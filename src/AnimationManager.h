#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Card.h"
#include <vector>
#include <cmath>

class AnimationManager {
public:
    static AnimationManager& Get() {
        static AnimationManager instance;
        return instance;
    }

    void UpdateCards(std::vector<Card>& cards, float deltaTime) {
        float lerpSpeed = 10.0f; // Vitesse d'interpolation
        for (auto& card : cards) {
            // Lerp Position
            card.position.x += (card.targetPosition.x - card.position.x) * lerpSpeed * deltaTime;
            card.position.y += (card.targetPosition.y - card.position.y) * lerpSpeed * deltaTime;

            // Lerp Scale
            card.scale += (card.targetScale - card.scale) * lerpSpeed * deltaTime;

            // Lerp Color
            card.color.r += (unsigned char)((card.targetColor.r - card.color.r) * lerpSpeed * deltaTime);
            card.color.g += (unsigned char)((card.targetColor.g - card.color.g) * lerpSpeed * deltaTime);
            card.color.b += (unsigned char)((card.targetColor.b - card.color.b) * lerpSpeed * deltaTime);
            card.color.a += (unsigned char)((card.targetColor.a - card.color.a) * lerpSpeed * deltaTime);
        }
    }

private:
    AnimationManager() {}
};

#endif // ANIMATION_MANAGER_H
