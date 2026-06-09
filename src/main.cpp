#include <raylib.h>
#include "NetworkManager.h"
#include "Board.h"
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

    gameBoard.Init(screenWidth, screenHeight);
    
    // Charger l'image de fond depuis l'artifact (assurez-vous du chemin ou copiez-le dans le dossier du jeu)
    // Pour l'instant on utilise un chemin absolu vers l'image générée
    gameBoard.LoadBackground("C:/Users/antoi/.gemini/antigravity-ide/brain/3ffb3821-ade3-40a3-acde-c983754c32e3/jjk_arena_board_1781000951051.png");

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        NetworkManager::Get().Update();
        gameBoard.Update(dt);

        BeginDrawing();
        
        gameBoard.Draw();

        if (!matchStarted) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
            if (NetworkManager::Get().IsConnected()) {
                DrawText("EN ATTENTE DU MATCHMAKING...", screenWidth / 2 - 200, screenHeight / 2, 30, GREEN);
            } else {
                DrawText("CONNEXION AU SERVEUR...", screenWidth / 2 - 200, screenHeight / 2, 30, ORANGE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
