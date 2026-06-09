#ifndef CARD_H
#define CARD_H

#include <string>
#include <raylib.h>

struct Card {
    std::string id;
    std::string name;
    int hp;
    int maxHp;
    int attack;
    int speed;
    int energyOccult;
    std::string imageUrl;
    Texture2D texture;

    // Propriétés visuelles (pour l'animation)
    Vector2 position;
    Vector2 targetPosition;
    float scale;
    float targetScale;
    Color color;
    Color targetColor;

    // Constructeur par défaut
    Card() : id(""), name("Unknown"), hp(100), maxHp(100), attack(10), speed(10), energyOccult(0),
             texture{0}, position{0, 0}, targetPosition{0, 0}, scale(1.0f), targetScale(1.0f),
             color(WHITE), targetColor(WHITE) {}
};

#endif // CARD_H
