#pragma once

#include <SFML/Graphics.hpp>
#include "src/game/player/buildModeType/BuildModeType.hpp"
#include "src/core/managers/classes/CharacterBody.hpp"

class WorldManager;

class Player final : public CharacterBody { 
public:
    Player();
    ~Player() override = default;

    void setPosition(const sf::Vector2f position) noexcept { CharacterBody::setPosition(position); }
    void setSpeed(float speed) noexcept { m_speed = speed; }
    void setAtlasTexture(const sf::Texture& texture) noexcept { m_playerAtlas = &texture; }
    
    [[nodiscard]] float getSpeed() const noexcept { return m_speed; }
    [[nodiscard]] sf::Vector2f getVisualPosition() const noexcept { return m_visualPosition; }
    [[nodiscard]] sf::Vector2f getHitboxSize() const noexcept { return HITBOX_SIZE; }
    [[nodiscard]] bool isOnGround() const noexcept { return CharacterBody::isOnGround(); }
    
    [[nodiscard]] sf::Vector2f getVelocity() noexcept { return CharacterBody::getVelocity(); }

    [[nodiscard]] ColliderType getType() const noexcept override { return ColliderType::DynamicEntity; }

    void handleEvent(const sf::Event& event, sf::RenderWindow& window, WorldManager& worldManager) noexcept;
    void update(float deltaTime) noexcept;
    void interpolate(float interpolationFactor) noexcept;
    void draw(sf::RenderTarget& target) const;

private:
    void modifyTileAtMouse(sf::RenderWindow& window, WorldManager& worldManager, bool isPlacing) noexcept;

    sf::Vector2f m_visualPosition;
    float m_speed{356.0f};
    bool m_isSprinting{false};

    BuildModeType m_buildMode = BuildModeType::Block;
    sf::VertexArray m_mesh;
    const sf::Texture* m_playerAtlas = nullptr; 

    static constexpr sf::Vector2f TEX_SIZE{16.0f, 32.0f};
    static constexpr sf::Vector2f SIZE{32.0f, 64.0f};
    static constexpr sf::Vector2f HITBOX_SIZE{25.0f, 50.0f}; 
};
