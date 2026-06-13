#include "Board.h"
#include "AnimationManager.h"
#include <iostream>

Board::Board() : m_screenWidth(0), m_screenHeight(0), m_background{0} {}

Board::~Board() {
    if (m_background.id != 0) {
        UnloadTexture(m_background);
    }
}

void Board::Init(int screenWidth, int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}

void Board::LoadBackground(const std::string& path) {
    m_background = LoadTexture("assets/background.png");
}

void Board::SetPlayerCards(const std::vector<Card>& cards) {
    m_playerCards = cards;
    // Positionnement initial au centre bas (spawn point)
    for (size_t i = 0; i < m_playerCards.size(); ++i) {
        m_playerCards[i].position = { (float)m_screenWidth / 2, (float)m_screenHeight + 200 };
        // Cible finale
        float spacing = 220.0f;
        float startX = (m_screenWidth - (cards.size() * spacing)) / 2.0f + spacing / 2.0f;
        m_playerCards[i].targetPosition = { startX + i * spacing, m_screenHeight - 180.0f };
        m_playerCards[i].scale = 1.0f;
        m_playerCards[i].targetScale = 1.0f;
        m_playerCards[i].color = WHITE;
        m_playerCards[i].targetColor = WHITE;
    }
}

void Board::SetOpponentCards(const std::vector<Card>& cards) {
    m_opponentCards = cards;
    for (size_t i = 0; i < m_opponentCards.size(); ++i) {
        m_opponentCards[i].position = { (float)m_screenWidth / 2, -200.0f };
        float spacing = 220.0f;
        float startX = (m_screenWidth - (cards.size() * spacing)) / 2.0f + spacing / 2.0f;
        m_opponentCards[i].targetPosition = { startX + i * spacing, 180.0f };
        m_opponentCards[i].scale = 1.0f;
        m_opponentCards[i].targetScale = 1.0f;
        m_opponentCards[i].color = WHITE;
        m_opponentCards[i].targetColor = WHITE;
    }
}

void Board::Update(float deltaTime) {
    AnimationManager::Get().UpdateCards(m_playerCards, deltaTime);
    AnimationManager::Get().UpdateCards(m_opponentCards, deltaTime);

    // Interaction souris pour le joueur
    Vector2 mousePos = GetMousePosition();
    for (auto& card : m_playerCards) {
        Rectangle cardRect = { card.position.x - 100 * card.scale, card.position.y - 150 * card.scale, 200 * card.scale, 300 * card.scale };
        if (CheckCollisionPointRec(mousePos, cardRect)) {
            card.targetScale = 1.1f; // Agrandir
            // Aura d'énergie occulte (légèrement violette)
            card.targetColor = { 220, 200, 255, 255 };
        } else {
            card.targetScale = 1.0f;
            card.targetColor = WHITE;
        }
    }
}

Board::PlayerAction Board::GetClickedAction() const {
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return {"none", -1};
    Vector2 mousePos = GetMousePosition();

    // Boutons d'attaque (milieu bas)
    float startX = m_screenWidth / 2.0f - 200.0f;
    float startY = m_screenHeight - 100.0f;
    for (int i = 0; i < 4; ++i) {
        Rectangle btn = { startX + i * 110, startY, 100, 40 };
        if (CheckCollisionPointRec(mousePos, btn)) {
            // Ignorer si la technique est vide
            if (m_playerCards.size() > 0 && m_playerCards[0].techniques[i].empty()) {
                continue;
            }
            return {"attack", i};
        }
    }

    // Boutons de switch (droite bas)
    float switchStartX = m_screenWidth - 350.0f;
    for (int i = 0; i < 3; ++i) { // max 3 switch dispo
        Rectangle btn = { switchStartX + i * 110, startY, 100, 40 };
        if (CheckCollisionPointRec(mousePos, btn)) {
            return {"switch", i + 1}; // index 0 est l'actif, on switch sur 1, 2 ou 3
        }
    }

    return {"none", -1};
}

void Board::DrawCard(const Card& card) {
    float width = 200 * card.scale;
    float height = 300 * card.scale;
    float x = card.position.x - width / 2;
    float y = card.position.y - height / 2;

    // Fond de la carte
    DrawRectangleRounded({x, y, width, height}, 0.1f, 10, card.color);
    DrawRectangleRoundedLines({x, y, width, height}, 0.1f, 10, 4.0f, DARKGRAY);

    // Nom de la carte
    DrawText(card.name.c_str(), x + 10, y + 10, 20 * card.scale, BLACK);

    // Stats
    DrawText(TextFormat("HP: %d/%d", card.hp, card.maxHp), x + 10, y + height - 100 * card.scale, 18 * card.scale, RED);
    DrawText(TextFormat("ATK: %d", card.attack), x + 10, y + height - 70 * card.scale, 18 * card.scale, DARKBLUE);
    DrawText(TextFormat("SPD: %d", card.speed), x + 10, y + height - 40 * card.scale, 18 * card.scale, ORANGE);
    DrawText(TextFormat("NRG: %d", card.energyOccult), x + 120 * card.scale, y + height - 40 * card.scale, 18 * card.scale, PURPLE);
}

void Board::Draw(bool drawUI) {
    if (m_background.id != 0) {
        // Dessiner le fond (étiré)
        DrawTexturePro(m_background, 
            {0, 0, (float)m_background.width, (float)m_background.height},
            {0, 0, (float)m_screenWidth, (float)m_screenHeight},
            {0, 0}, 0.0f, WHITE);
    } else {
        ClearBackground(RAYWHITE);
    }

    for (const auto& card : m_opponentCards) {
        DrawCard(card);
    }
    for (const auto& card : m_playerCards) {
        DrawCard(card);
    }

    if (!drawUI || m_playerCards.empty()) return;

    // UI Panel (fond)
    DrawRectangle(0, m_screenHeight - 120, m_screenWidth, 120, {20, 20, 30, 220});
    DrawLine(0, m_screenHeight - 120, m_screenWidth, m_screenHeight - 120, RAYWHITE);

    // Dessiner les boutons d'attaques
    float startX = m_screenWidth / 2.0f - 200.0f;
    float startY = m_screenHeight - 100.0f;
    DrawText("Techniques", startX, startY - 25, 20, RAYWHITE);
    
    for (int i = 0; i < 4; ++i) {
        Rectangle btn = { startX + i * 110, startY, 100, 40 };
        Vector2 mousePos = GetMousePosition();
        
        std::string tName = m_playerCards[0].techniques[i];
        bool isEmpty = tName.empty();
        
        Color btnColor;
        if (isEmpty) {
            btnColor = {60, 60, 60, 255}; // Grisé
        } else {
            btnColor = CheckCollisionPointRec(mousePos, btn) ? RED : DARKGRAY;
        }
        
        DrawRectangleRec(btn, btnColor);
        DrawRectangleLinesEx(btn, 2, isEmpty ? GRAY : RAYWHITE);
        
        if (isEmpty) {
            DrawLineEx({btn.x, btn.y}, {btn.x + btn.width, btn.y + btn.height}, 2, RED); // Barré
            DrawText("Vide", btn.x + 30, btn.y + 12, 16, GRAY);
        } else {
            // Tronquer le nom si trop long
            std::string dispName = tName.length() > 8 ? tName.substr(0, 6) + ".." : tName;
            DrawText(dispName.c_str(), btn.x + 10, btn.y + 12, 16, RAYWHITE);
        }
    }

    // Dessiner les boutons de switch
    float switchStartX = m_screenWidth - 350.0f;
    DrawText("Switch Perso", switchStartX, startY - 25, 20, RAYWHITE);
    for (int i = 0; i < 3; ++i) {
        Rectangle btn = { switchStartX + i * 110, startY, 100, 40 };
        Vector2 mousePos = GetMousePosition();
        
        bool canSwitch = (i + 1) < m_playerCards.size();
        Color btnColor;
        
        if (!canSwitch) {
            btnColor = {60, 60, 60, 255};
        } else {
            btnColor = CheckCollisionPointRec(mousePos, btn) ? BLUE : DARKGRAY;
        }
        
        DrawRectangleRec(btn, btnColor);
        DrawRectangleLinesEx(btn, 2, canSwitch ? RAYWHITE : GRAY);
        
        if (canSwitch) {
            std::string cName = m_playerCards[i + 1].name;
            std::string dispName = cName.length() > 8 ? cName.substr(0, 6) + ".." : cName;
            DrawText(dispName.c_str(), btn.x + 10, btn.y + 12, 16, RAYWHITE);
        } else {
            DrawLineEx({btn.x, btn.y}, {btn.x + btn.width, btn.y + btn.height}, 2, GRAY); // Barré
            DrawText("Vide", btn.x + 30, btn.y + 12, 16, GRAY);
        }
    }
}
