#ifndef BOARD_H
#define BOARD_H

#include "Card.h"
#include <vector>
#include <string>

class Board {
public:
    Board();
    ~Board();

    void Init(int screenWidth, int screenHeight);
    void Update(float deltaTime);
    void Draw();

    void LoadBackground(const std::string& path);
    void SetPlayerCards(const std::vector<Card>& cards);
    void SetOpponentCards(const std::vector<Card>& cards);

    struct PlayerAction {
        std::string type; // "none", "attack", "switch"
        int index; // techniqueIndex or switchToIndex
    };

    PlayerAction GetClickedAction() const;

private:
    int m_screenWidth;
    int m_screenHeight;
    Texture2D m_background;

    std::vector<Card> m_playerCards;
    std::vector<Card> m_opponentCards;

    void DrawCard(const Card& card);
};

#endif // BOARD_H
