#include "src/core/managers/physic/PhysicManager.hpp"
#include "src/game/worldManager/WorldManager.hpp"
#include <cmath>

PhysicManager::PhysicManager() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    
    worldDef.gravity = b2Vec2{ 0.0f, 26.0f }; 
    
    m_worldId = b2CreateWorld(&worldDef);
}

PhysicManager::~PhysicManager() {
    if (b2World_IsValid(m_worldId)) {
        b2DestroyWorld(m_worldId);
    }
}

void PhysicManager::addCollider(Collider* collider) noexcept {
    if (collider) m_dynamicColliders.push_back(collider);
}

void PhysicManager::removeCollider(Collider* collider) noexcept {
    std::erase(m_dynamicColliders, collider);
}

void PhysicManager::clear() noexcept {
    m_dynamicColliders.clear();
}

void PhysicManager::update(float dt, WorldManager& worldManager, unsigned int tileSize) noexcept {
    const float fTileSize = static_cast<float>(tileSize);

    for (b2BodyId blockId : m_temporaryStaticBlocks) {
        if (b2Body_IsValid(blockId)) b2DestroyBody(blockId);
    }
    m_temporaryStaticBlocks.clear();

    for (auto* moving : m_dynamicColliders) {
        if (moving->getType() == ColliderType::StaticBlock) continue;

        sf::Vector2f pos = moving->getPosition();
        sf::Vector2f size = moving->getSize();

        int startX = static_cast<int>(std::floor((pos.x - fTileSize * 3.f) / fTileSize));
        int endX   = static_cast<int>(std::floor((pos.x + size.x + fTileSize * 3.f) / fTileSize));
        int startY = static_cast<int>(std::floor((pos.y - fTileSize * 3.f) / fTileSize));
        int endY   = static_cast<int>(std::floor((pos.y + size.y + fTileSize * 3.f) / fTileSize));

        for (int x = startX; x <= endX; ++x) {
            for (int y = startY; y <= endY; ++y) {
                float blockX = static_cast<float>(x * static_cast<int>(tileSize));
                float blockY = static_cast<float>(y * static_cast<int>(tileSize));

                if (worldManager.isSolidBlockAt(blockX, blockY)) {
                    b2BodyDef bodyDef = b2DefaultBodyDef();
                    bodyDef.type = b2_staticBody;
                    bodyDef.position = b2Vec2{ (blockX + fTileSize/2.0f) / 32.0f, (blockY + fTileSize/2.0f) / 32.0f };

                    b2BodyId blockId = b2CreateBody(m_worldId, &bodyDef);

                    b2Polygon box = b2MakeBox(fTileSize / 64.0f, fTileSize / 64.0f);
                    b2ShapeDef shapeDef = b2DefaultShapeDef();
                    
                    b2CreatePolygonShape(blockId, &shapeDef, &box);

                    m_temporaryStaticBlocks.push_back(blockId);
                }
            }
        }
    }

    b2World_Step(m_worldId, dt, 4);
}
