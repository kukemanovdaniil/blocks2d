#include "src/core/managers/physic/PhysicManager.hpp"
#include "src/core/managers/physic/AdvancedSweptPhysics.hpp"
#include <cmath>

#include "src/game/worldManager/WorldManager.hpp"

#include "src/core/managers/physic/PhysicManager.hpp"
#include "src/core/managers/physic/AdvancedSweptPhysics.hpp"
#include <cmath>
#include <algorithm>

#include "src/game/worldManager/WorldManager.hpp"

void PhysicManager::update(float dt, WorldManager& worldManager, unsigned int tileSize) noexcept {
    const float fTileSize = static_cast<float>(tileSize);
    m_blockFlyweight.size = sf::Vector2f(fTileSize, fTileSize);

    for (auto* moving : m_dynamicColliders) {
        if (moving->getType() == ColliderType::StaticBlock) continue;

        sf::Vector2f velocity = moving->getVelocity();
        if (velocity.x == 0.0f && velocity.y == 0.0f) continue;

        float timeRemaining = 1.0f;
        
        for (int iteration = 0; iteration < 3; ++iteration) {
            if (timeRemaining <= 0.0f) break;

            sf::Vector2f deltaMove = velocity * (dt * timeRemaining);
            if (deltaMove.x == 0.0f && deltaMove.y == 0.0f) break;

            sf::Vector2f pos = moving->getPosition();
            sf::Vector2f size = moving->getSize();

            int startX = static_cast<int>(std::floor(std::min(pos.x, pos.x + deltaMove.x) / fTileSize)) - 1;
            int endX = static_cast<int>(std::floor(std::max(pos.x + size.x, pos.x + size.x + deltaMove.x) / fTileSize)) + 1;
            int startY = static_cast<int>(std::floor(std::min(pos.y, pos.y + deltaMove.y) / fTileSize)) - 1;
            int endY = static_cast<int>(std::floor(std::max(pos.y + size.y, pos.y + size.y + deltaMove.y) / fTileSize)) + 1;

            RaycastHit closestBlockHit;
            closestBlockHit.hitTime = 1.0f; 

            for (int x = startX; x <= endX; ++x) {
                for (int y = startY; y <= endY; ++y) {
                    float blockX = static_cast<float>(x * tileSize);
                    float blockY = static_cast<float>(y * tileSize);

                    if (worldManager.isSolidBlockAt(blockX, blockY)) { 
                        m_blockFlyweight.position = sf::Vector2f(blockX, blockY);

                        RaycastHit hit = AdvancedSweptPhysics::checkCollision(*moving, m_blockFlyweight, dt * timeRemaining);
                        
                        if (hit.collided) {
                            if (std::abs(hit.normal.x) > 0.0f) {
                                float blockAboveY = blockY - fTileSize;
                                
                                if (!worldManager.isSolidBlockAt(blockX, blockAboveY)) {
                                    float playerBottom = pos.y + size.y;
                                    
                                    if (playerBottom <= blockY + 6.0f) {
                                        continue;
                                    }
                                }
                            }
                            if (hit.hitTime < closestBlockHit.hitTime) {
                                closestBlockHit = hit;
                            }
                        }
                    }
                }
            }

            if (closestBlockHit.collided) {
                float safeHitTime = std::max(0.0f, closestBlockHit.hitTime - 0.001f);
                moving->move(velocity * (dt * timeRemaining * safeHitTime));
                
                moving->onCollision(m_blockFlyweight, closestBlockHit.normal);
                
                if (std::abs(closestBlockHit.normal.x) > 0.0f) velocity.x = 0.0f;
                if (std::abs(closestBlockHit.normal.y) > 0.0f) velocity.y = 0.0f;

                timeRemaining -= closestBlockHit.hitTime;
            } 
            else {
                moving->move(deltaMove);
                break;
            }
        }
    }
}
