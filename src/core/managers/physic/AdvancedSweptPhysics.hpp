#pragma once
#include "src/core/managers/physic/collider/Collider.hpp"
#include <algorithm>
#include <limits>
#include <cmath>

class AdvancedSweptPhysics {
public:
    [[nodiscard]] static constexpr RaycastHit checkCollision(const Collider& moving, const Collider& target, float dt) noexcept {
        RaycastHit hit;

        const auto movingPos  = moving.getPosition();
        const auto movingSize = moving.getSize();
        const auto targetPos  = target.getPosition();
        const auto targetSize = target.getSize();

        const sf::Vector2f relativeVelocity = moving.getVelocity() - target.getVelocity();
        const sf::Vector2f deltaMove = relativeVelocity * dt;

        if (deltaMove.x == 0.0f && deltaMove.y == 0.0f) return hit;

        const sf::Vector2f expandedPos  = targetPos - movingSize / 2.0f;
        const sf::Vector2f expandedSize = targetSize + movingSize;
        const sf::Vector2f movingCenter = movingPos + movingSize / 2.0f;

        sf::Vector2f invEntry, invExit;

        if (deltaMove.x > 0.0f) {
            invEntry.x = expandedPos.x - movingCenter.x;
            invExit.x  = (expandedPos.x + expandedSize.x) - movingCenter.x;
        } else {
            invEntry.x = (expandedPos.x + expandedSize.x) - movingCenter.x;
            invExit.x  = expandedPos.x - movingCenter.x;
        }

        if (deltaMove.y > 0.0f) {
            invEntry.y = expandedPos.y - movingCenter.y;
            invExit.y  = (expandedPos.y + expandedSize.y) - movingCenter.y;
        } else {
            invEntry.y = (expandedPos.y + expandedSize.y) - movingCenter.y;
            invExit.y  = expandedPos.y - movingCenter.y;
        }

        sf::Vector2f entryTime, exitTime;
        constexpr float inf = std::numeric_limits<float>::infinity();

        entryTime.x = (deltaMove.x != 0.0f) ? invEntry.x / deltaMove.x : -inf;
        exitTime.x  = (deltaMove.x != 0.0f) ? invExit.x / deltaMove.x  :  inf;

        entryTime.y = (deltaMove.y != 0.0f) ? invEntry.y / deltaMove.y : -inf;
        exitTime.y  = (deltaMove.y != 0.0f) ? invExit.y / deltaMove.y  :  inf;

        const float entryTimeMax = std::max(entryTime.x, entryTime.y);
        const float exitTimeMin  = std::min(exitTime.x, exitTime.y);

        if (entryTimeMax > exitTimeMin || 
            (entryTime.x < 0.0f && entryTime.y < 0.0f) || 
            entryTime.x > 1.0f || entryTime.y > 1.0f) 
        {
            return hit; 
        }

        hit.collided = true;
        hit.hitTime = entryTimeMax;

        if (entryTime.x > entryTime.y) {
            hit.normal = (deltaMove.x > 0.0f) ? sf::Vector2f(-1.0f, 0.0f) : sf::Vector2f(1.0f, 0.0f);
        } else {
            hit.normal = (deltaMove.y > 0.0f) ? sf::Vector2f(0.0f, -1.0f) : sf::Vector2f(0.0f, 1.0f);
        }

        return hit;
    }
};
