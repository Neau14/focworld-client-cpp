#include <raylib.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "NetworkManager.h"
#include "Board.h"
#include "AutoUpdater.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using json = nlohmann::json;

#ifndef SERVER_URL
#define SERVER_URL "ws://localhost:4000"
#endif

#ifdef _WIN32
std::string g_newUriReceived = "";
bool g_hasNewUri = false;
WNDPROC g_originalWndProc = nullptr;

LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_COPYDATA) {
        COPYDATASTRUCT* cds = (COPYDATASTRUCT*)lParam;
        if (cds->dwData == 1) {
            g_newUriReceived = std::string((char*)cds->lpData);
            g_hasNewUri = true;
        }
        return 1;
    }
    return CallWindowProc(g_originalWndProc, hwnd, msg, wParam, lParam);
}
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
    HWND existingHwnd = FindWindowA(NULL, "FOC World TCG - Arene de Combat");
    if (existingHwnd != NULL) {
        if (argc > 1) {
            std::string uri(argv[1]);
            COPYDATASTRUCT cds;
            cds.dwData = 1;
            cds.cbData = uri.length() + 1;
            cds.lpData = (PVOID)uri.c_str();
            SendMessage(existingHwnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds);
        }
        ShowWindow(existingHwnd, SW_RESTORE);
        SetForegroundWindow(existingHwnd);
        return 0; // Exit this instance
    }
#endif

    std::string matchId = "Inconnu";
    std::string token = "Inconnu";

    if (argc > 1) {
        std::string uri(argv[1]);
        std::regex uri_regex(R"(foc-tcg://match/([^?]+)\?token=(.+))");
        std::smatch match;

        if (std::regex_search(uri, match, uri_regex)) {
            matchId = match[1].str();
            token = match[2].str();
        }
    }

    std::string serverUrl = SERVER_URL;
    Board gameBoard;
    bool matchStarted = false;
    
    NetworkManager::Get().OnMessageReceived([&](const std::string& type, const std::string& data) {
        if (type == "match_found") {
            try {
                json payload = json::parse(data);
                std::vector<Card> playerCards;
                std::vector<Card> opponentCards;

                // On simule le parsing des decks
                // Le payload contient { playerDeck: [...], opponentDeck: [...] }
                if (payload.contains("playerDeck")) {
                    for (auto& item : payload["playerDeck"]) {
                        Card c;
                        c.name = item.value("name", "Inconnu");
                        c.hp = item.value("health", 100);
                        c.maxHp = c.hp;
                        c.attack = item.value("strength", 10);
                        c.speed = item.value("speed", 10);
                        c.energyOccult = item.value("cursedEnergy", 0);
                        playerCards.push_back(c);
                    }
                }
                
                if (payload.contains("opponentDeck")) {
                    for (auto& item : payload["opponentDeck"]) {
                        Card c;
                        c.name = item.value("name", "Inconnu");
                        c.hp = item.value("health", 100);
                        c.maxHp = c.hp;
                        c.attack = item.value("strength", 10);
                        c.speed = item.value("speed", 10);
                        c.energyOccult = item.value("cursedEnergy", 0);
                        opponentCards.push_back(c);
                    }
                }

                gameBoard.SetPlayerCards(playerCards);
                gameBoard.SetOpponentCards(opponentCards);
                matchStarted = true;

            } catch (const std::exception& e) {
                std::cerr << "JSON Parse error: " << e.what() << "\n";
            }
        }
    });
    
    NetworkManager::Get().Connect(serverUrl, matchId, token);

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "FOC World TCG - Arene de Combat");
    SetTargetFPS(60);

#ifdef _WIN32
    HWND hwnd = (HWND)GetWindowHandle();
    g_originalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)CustomWndProc);
#endif

    AutoUpdater::Get().CheckForUpdates();

    gameBoard.Init(screenWidth, screenHeight);
    
    // Charger l'image de fond depuis l'artifact (assurez-vous du chemin ou copiez-le dans le dossier du jeu)
    // Pour l'instant on utilise un chemin absolu vers l'image générée
    gameBoard.LoadBackground("C:/Users/antoi/.gemini/antigravity-ide/brain/3ffb3821-ade3-40a3-acde-c983754c32e3/jjk_arena_board_1781000951051.png");

    while (!WindowShouldClose()) {
#ifdef _WIN32
        if (g_hasNewUri) {
            std::regex uri_regex(R"(foc-tcg://match/([^?]+)\?token=(.+))");
            std::smatch match;
            if (std::regex_search(g_newUriReceived, match, uri_regex)) {
                matchId = match[1].str();
                token = match[2].str();
                NetworkManager::Get().Connect(serverUrl, matchId, token);
                matchStarted = false; // Reset to wait for matchmaking
            }
            g_hasNewUri = false;
            g_newUriReceived = "";
        }
#endif

        float dt = GetFrameTime();
        NetworkManager::Get().Update();
        gameBoard.Update(dt);

        BeginDrawing();
        
        UpdaterState state = AutoUpdater::Get().GetState();
        if (state != UpdaterState::UP_TO_DATE && state != UpdaterState::IDLE && state != UpdaterState::FAILED) {
            ClearBackground(DARKGRAY);
            if (state == UpdaterState::CHECKING) {
                DrawText("Recherche de mises a jour...", screenWidth / 2 - 200, screenHeight / 2, 30, LIGHTGRAY);
            } else if (state == UpdaterState::UPDATE_AVAILABLE) {
                DrawText("Mise a jour disponible ! Telechargement en cours...", screenWidth / 2 - 350, screenHeight / 2, 30, YELLOW);
                AutoUpdater::Get().StartDownload();
            } else if (state == UpdaterState::DOWNLOADING) {
                DrawText("Telechargement de la mise a jour en cours...", screenWidth / 2 - 300, screenHeight / 2, 30, ORANGE);
            } else if (state == UpdaterState::READY_TO_INSTALL) {
                DrawText("Pret a installer ! Le jeu va redemarrer...", screenWidth / 2 - 300, screenHeight / 2, 30, GREEN);
                EndDrawing();
                AutoUpdater::Get().InstallAndExit();
                continue;
            }
        } else {
            gameBoard.Draw();

            if (!matchStarted) {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
                if (NetworkManager::Get().IsConnected()) {
                    DrawText("EN ATTENTE DU MATCHMAKING...", screenWidth / 2 - 200, screenHeight / 2, 30, GREEN);
                } else {
                    DrawText("CONNEXION AU SERVEUR...", screenWidth / 2 - 200, screenHeight / 2, 30, ORANGE);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
