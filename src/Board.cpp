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
    m_background = LoadTexture(path.c_str());
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

void Board::Draw() {
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
}
