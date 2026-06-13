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

    // Techniques équipées (noms). Chaîne vide si aucun équipement dans le slot
    std::string techniques[4];

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
             color(WHITE), targetColor(WHITE) {
        techniques[0] = "";
        techniques[1] = "";
        techniques[2] = "";
        techniques[3] = "";
    }
};

#endif // CARD_H
