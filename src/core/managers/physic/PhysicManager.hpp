#pragma once
#include <box2d/box2d.h>
#include <vector>
#include "src/core/managers/classes/CharacterBody.hpp"

class WorldManager;

class PhysicManager {
public:
    PhysicManager();
    ~PhysicManager();

    void addCollider(Collider* collider) noexcept;
    void removeCollider(Collider* collider) noexcept;
    void clear() noexcept;

    void update(float dt, WorldManager& worldManager, unsigned int tileSize) noexcept;

    [[nodiscard]] b2WorldId getWorldId() const noexcept { return m_worldId; }

private:
    b2WorldId m_worldId;
    std::vector<Collider*> m_dynamicColliders;
    std::vector<b2BodyId> m_temporaryStaticBlocks;
};
