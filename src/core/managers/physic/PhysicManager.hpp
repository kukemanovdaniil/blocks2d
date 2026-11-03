#pragma once
#include <vector>
#include <algorithm>
#include <span>
#include "src/core/managers/physic/collider/Collider.hpp"

class WorldManager;

class FlyweightBlockCollider final : public Collider {
public:
    sf::Vector2f position;
    sf::Vector2f size;

    void move(const sf::Vector2f&) noexcept override {} 
    void onCollision(Collider&, const sf::Vector2f&) override {}
    [[nodiscard]] ColliderType getType() const noexcept override { return ColliderType::StaticBlock; }

protected:
    [[nodiscard]] sf::Vector2f implPosition() const noexcept override { return position; }
    [[nodiscard]] sf::Vector2f implSize() const noexcept override { return size; }
    [[nodiscard]] sf::Vector2f implVelocity() const noexcept override { return {0.0f, 0.0f}; }
};

class PhysicManager {
public:
    PhysicManager() = default;
    ~PhysicManager() = default;

    PhysicManager(const PhysicManager&) = delete;
    PhysicManager& operator=(const PhysicManager&) = delete;

    void addCollider(Collider* collider) noexcept {
        if (collider) m_dynamicColliders.push_back(collider);
    }

    void removeCollider(Collider* collider) noexcept {
        std::erase(m_dynamicColliders, collider);
    }

    void clear() noexcept { m_dynamicColliders.clear(); }

    void update(float dt, WorldManager& worldManager, unsigned int tileSize) noexcept;

private:
    std::vector<Collider*> m_dynamicColliders;
    FlyweightBlockCollider m_blockFlyweight;
};
