#pragma once

#include <box2d/box2d.h>
#include <vector>
#include <map>
#include <utility>
#include <SFML/System/Vector2.hpp>
#include "src/core/managers/physic/collider/Collider.hpp"

class WorldManager;

class PhysicManager {
public:
    PhysicManager();
    ~PhysicManager();

    PhysicManager(const PhysicManager&) = delete;
    PhysicManager& operator=(const PhysicManager&) = delete;

    void addCollider(Collider* collider) noexcept;
    void removeCollider(Collider* collider) noexcept;
    void clear() noexcept;

    void update(float dt, WorldManager& worldManager, float tileSize) noexcept;

    b2WorldId getWorldId() const noexcept { return m_worldId; }

private:
    void createBlockBody(int gridX, int gridY, float tileSize) noexcept;
    void destroyBlockBody(int gridX, int gridY) noexcept;
    
    void updateGridColliders(WorldManager& worldManager, float tileSize) noexcept;

private:
    b2WorldId m_worldId;
    std::vector<Collider*> m_dynamicColliders;

    std::map<std::pair<int, int>, b2BodyId> m_activeBlocks;
    
    int m_lastPlayerGridX;
    int m_lastPlayerGridY;
};
