#include "PhysicManager.hpp"
#include "src/game/worldManager/WorldManager.hpp"
#include <algorithm>
#include <cmath>
#include <set>

PhysicManager::PhysicManager() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, 26.0f };
    m_worldId = b2CreateWorld(&worldDef);
}

PhysicManager::~PhysicManager() {
    for (auto& [key, blockId] : m_activeBlocks) {
        if (b2Body_IsValid(blockId)) b2DestroyBody(blockId);
    }
    m_activeBlocks.clear();

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

void PhysicManager::createBlockBody(int gridX, int gridY, float tileSize) noexcept {
    std::pair<int, int> key = { gridX, gridY };
    if (m_activeBlocks.contains(key)) return;

    float blockX = static_cast<float>(gridX) * tileSize;
    float blockY = static_cast<float>(gridY) * tileSize;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.position = b2Vec2{ (blockX + tileSize / 2.0f) / 32.0f, (blockY + tileSize / 2.0f) / 32.0f };

    b2BodyId blockId = b2CreateBody(m_worldId, &bodyDef);

    b2Polygon box = b2MakeBox(tileSize / 64.0f, tileSize / 64.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.5f;
    shapeDef.material.restitution = 0.0f;

    b2CreatePolygonShape(blockId, &shapeDef, &box);
    m_activeBlocks[key] = blockId;
}

void PhysicManager::destroyBlockBody(int gridX, int gridY) noexcept {
    std::pair<int, int> key = { gridX, gridY };
    auto it = m_activeBlocks.find(key);
    if (it != m_activeBlocks.end()) {
        if (b2Body_IsValid(it->second)) {
            b2DestroyBody(it->second);
        }
        m_activeBlocks.erase(it);
    }
}

void PhysicManager::updateGridColliders(WorldManager& worldManager, float tileSize) noexcept {
    if (m_dynamicColliders.empty()) return;

    sf::Vector2f playerPos = m_dynamicColliders[0]->getPosition();
    
    int currentPlayerGridX = static_cast<int>(std::floor(playerPos.x / tileSize));
    int currentPlayerGridY = static_cast<int>(std::floor(playerPos.y / tileSize));

    if (currentPlayerGridX == m_lastPlayerGridX && currentPlayerGridY == m_lastPlayerGridY) {
        return; 
    }

    m_lastPlayerGridX = currentPlayerGridX;
    m_lastPlayerGridY = currentPlayerGridY;

    const int RADIUS = 8; 

    int startX = currentPlayerGridX - RADIUS;
    int endX   = currentPlayerGridX + RADIUS;
    int startY = currentPlayerGridY - RADIUS;
    int endY   = currentPlayerGridY + RADIUS;

    std::set<std::pair<int, int>> requiredBlocks;

    for (int x = startX; x <= endX; ++x) {
        for (int y = startY; y <= endY; ++y) {
            float pixelX = static_cast<float>(x) * tileSize;
            float pixelY = static_cast<float>(y) * tileSize;

            if (worldManager.isSolidBlockAt(pixelX, pixelY)) {
                std::pair<int, int> key = { x, y };
                requiredBlocks.insert(key);
                
                createBlockBody(x, y, tileSize);
            }
        }
    }

    for (auto it = m_activeBlocks.begin(); it != m_activeBlocks.end();) {
        if (!requiredBlocks.contains(it->first)) {
            if (b2Body_IsValid(it->second)) {
                b2DestroyBody(it->second);
            }
            it = m_activeBlocks.erase(it);
        } else {
            ++it;
        }
    }
}

void PhysicManager::update(float dt, WorldManager& worldManager, float tileSize) noexcept {
    updateGridColliders(worldManager, tileSize);

    b2World_Step(m_worldId, dt, 4);
}
