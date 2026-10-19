#pragma once

#include <SFML/Graphics.hpp>
#include "src/game/player/buildModeType/BuildModeType.hpp"

class WorldManager;

class Player {
public:
    Player();



    // SETTERS
    void setPosition(const sf::Vector2f position) noexcept { m_position = position; }
    void setSpeed(float speed) noexcept { m_speed = speed; }
    void setAtlasTexture(const sf::Texture& texture) { m_playerAtlas = &texture; }



    // GETTERS
    [[nodiscard]] float getSpeed() const noexcept { return m_speed; }
    [[nodiscard]] sf::Vector2f getPosition() const noexcept { return m_position; }
    [[nodiscard]] sf::Vector2f getVusialPosition() const noexcept { return m_visualPosition; }
    [[nodiscard]] sf::Vector2f getSize() const noexcept { return SIZE; }



    // OTHER
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, WorldManager& worldManager) noexcept;
    void update(float deltaTime) noexcept;
    void interpolate(float interpolationFactor) noexcept;
    
    void draw(sf::RenderTarget& target) const;

    void placeTile(sf::RenderWindow& window, WorldManager& worldManager) noexcept;
    void breakTile(sf::RenderWindow& window, WorldManager& worldManager) noexcept;

private:
    sf::Vector2f m_previousPosition;
    sf::Vector2f m_position;
    sf::Vector2f m_visualPosition;
    float m_speed{356.0f};
    bool m_isSprinting{false};

    BuildModeType m_buildMode = BuildModeType::Block;

    sf::VertexArray m_vertices;

    const sf::Texture* m_playerAtlas = nullptr; 

    static constexpr sf::Vector2f SIZE{32.0f, 64.0f};
};
