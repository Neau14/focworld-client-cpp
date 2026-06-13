#include <raylib.h>
#ifdef _WIN32
#include "WindowsUtils.h"
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

int main(int argc, char* argv[]) {
#ifdef _WIN32
    Windows_CheckSingleInstance(argc, argv);
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
        if (type == "match_found" || type == "game_state" || type == "round_result") {
            try {
                json payload = json::parse(data);
                json gameState = payload;
                
                // Si c'est match_found ou round_result, le gameState est imbriqué
                if (payload.contains("gameState")) {
                    gameState = payload["gameState"];
                }
                
                std::vector<Card> playerCards;
                std::vector<Card> opponentCards;

                auto parseCard = [](const json& item) -> Card {
                    Card c;
                    c.id = item.value("id", "");
                    c.name = item.value("name", "Inconnu");
                    c.hp = item.value("currentHp", 100);
                    c.maxHp = item.value("maxHp", 100);
                    
                    if (item.contains("stats")) {
                        c.attack = item["stats"].value("atk", 10);
                        c.speed = item["stats"].value("spd", 10);
                    } else {
                        c.attack = item.value("strength", 10); // legacy fallback
                        c.speed = item.value("speed", 10);
                    }
                    c.energyOccult = item.value("currentEnergy", 0);
                    c.imageUrl = item.value("imageUrl", "");
                    return c;
                };

                if (gameState.contains("myDeck")) {
                    for (auto& item : gameState["myDeck"]) {
                        playerCards.push_back(parseCard(item));
                    }
                }
                
                if (gameState.contains("opponentDeck")) {
                    for (auto& item : gameState["opponentDeck"]) {
                        opponentCards.push_back(parseCard(item));
                    }
                }

                gameBoard.SetPlayerCards(playerCards);
                gameBoard.SetOpponentCards(opponentCards);
                matchStarted = true;

            } catch (const std::exception& e) {
                std::cerr << "JSON Parse error (" << type << "): " << e.what() << "\nData: " << data << "\n";
            }
        }
        else if (type == "game_end") {
            try {
                json payload = json::parse(data);
                std::cout << "Le match est terminé ! Vainqueur : " << payload.value("winnerId", "Inconnu") << std::endl;
                // TODO: Afficher l'écran de fin
            } catch (const std::exception& e) {
                std::cerr << "JSON Parse error (game_end): " << e.what() << "\n";
            }
        }
    });
    
    NetworkManager::Get().Connect(serverUrl, matchId, token);

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "FOC World TCG - Arene de Combat");
    SetTargetFPS(60);

#ifdef _WIN32
    Windows_SetupCustomWndProc();
#endif

    AutoUpdater::Get().CheckForUpdates();

    gameBoard.Init(screenWidth, screenHeight);
    
    // Charger l'image de fond depuis l'artifact (assurez-vous du chemin ou copiez-le dans le dossier du jeu)
    // Pour l'instant on utilise un chemin absolu vers l'image générée
    gameBoard.LoadBackground("C:/Users/antoi/.gemini/antigravity-ide/brain/3ffb3821-ade3-40a3-acde-c983754c32e3/jjk_arena_board_1781000951051.png");

    while (!WindowShouldClose()) {
#ifdef _WIN32
        if (Windows_HasNewUri()) {
            std::string newUriReceived = Windows_GetNewUri();
            std::regex uri_regex(R"(foc-tcg://match/([^?]+)\?token=(.+))");
            std::smatch match;
            if (std::regex_search(newUriReceived, match, uri_regex)) {
                matchId = match[1].str();
                token = match[2].str();
                NetworkManager::Get().Connect(serverUrl, matchId, token);
                matchStarted = false; // Reset to wait for matchmaking
            }
            Windows_ClearNewUri();
        }
#endif

        float dt = GetFrameTime();
        NetworkManager::Get().Update();
        gameBoard.Update(dt);

        if (matchStarted) {
            Board::PlayerAction pAction = gameBoard.GetClickedAction();
            if (pAction.type != "none") {
                json action;
                if (pAction.type == "attack") {
                    action = {
                        {"type", "attack"},
                        {"techniqueIndex", pAction.index}
                    };
                    std::cout << "Action envoyee : attaque (technique " << pAction.index << ")" << std::endl;
                } else if (pAction.type == "switch") {
                    action = {
                        {"type", "switch"},
                        {"switchToIndex", pAction.index}
                    };
                    std::cout << "Action envoyee : switch sur carte " << pAction.index << std::endl;
                }
                
                json payload = {
                    {"matchId", matchId},
                    {"action", action}
                };
                NetworkManager::Get().SendJSON("select_action", payload.dump());
            }
        }

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
