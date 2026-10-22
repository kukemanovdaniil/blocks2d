#include "Player.hpp"

#include <SFML/Graphics.hpp>
#include "src/game/worldManager/WorldManager.hpp"
#include <cmath>

Player::Player() {
    m_mesh.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_mesh.resize(6);

    sf::Vector2f actualSize = SIZE;
    float halfX = actualSize.x / 2.0f;
    float halfY = actualSize.y / 2.0f;

    float posX0 = -halfX;
    float posX1 =  halfX;
    float posY0 = -halfY;
    float posY1 =  halfY;

    float texX0 = 0.0f;
    float texX1 = TEX_SIZE.x;
    float texY0 = 0.0f;
    float texY1 = TEX_SIZE.y;

    m_mesh[0].position = sf::Vector2f(posX0, posY0);
    m_mesh[0].texCoords = sf::Vector2f(texX0, texY0);

    m_mesh[1].position = sf::Vector2f(posX0, posY1);
    m_mesh[1].texCoords = sf::Vector2f(texX0, texY1);

    m_mesh[2].position = sf::Vector2f(posX1, posY0);
    m_mesh[2].texCoords = sf::Vector2f(texX1, texY0);



    m_mesh[3].position = sf::Vector2f(posX0, posY1);
    m_mesh[3].texCoords = sf::Vector2f(texX0, texY1);

    m_mesh[4].position = sf::Vector2f(posX1, posY1);
    m_mesh[4].texCoords = sf::Vector2f(texX1, texY1);

    m_mesh[5].position = sf::Vector2f(posX1, posY0);
    m_mesh[5].texCoords = sf::Vector2f(texX1, texY0);
}


void Player::placeTile(sf::RenderWindow& window, WorldManager& worldManager) noexcept {
    if (m_buildMode == BuildModeType::Block || m_buildMode == BuildModeType::Wall) {
        sf::Vector2i mousePos{sf::Mouse::getPosition(window)};
        sf::Vector2f worldPos{window.mapPixelToCoords(mousePos)};

        int tileX{static_cast<int>(std::floor(worldPos.x / 32.0f))};

        int tileY{static_cast<int>(std::floor(worldPos.y / 32.0f))};
        tileY = static_cast<int>(CHUNK_H) - 1 - tileY;

        if (m_buildMode == BuildModeType::Block) {
            worldManager.setGlobalBlock(tileX, tileY, BlockType::Limestone);
        }
        else {
            worldManager.setGlobalWall(tileX, tileY, WallType::Limestone);
        } 
    }
}

void Player::breakTile(sf::RenderWindow& window, WorldManager& worldManager) noexcept {
    if (m_buildMode == BuildModeType::Block || m_buildMode == BuildModeType::Wall) {
        sf::Vector2i mousePos{sf::Mouse::getPosition(window)};
        sf::Vector2f worldPos{window.mapPixelToCoords(mousePos)};

        int tileX{static_cast<int>(std::floor(worldPos.x / 32.0f))};

        int tileY{static_cast<int>(std::floor(worldPos.y / 32.0f))};
        tileY = static_cast<int>(CHUNK_H) - 1 - tileY;

        if (m_buildMode == BuildModeType::Block) {
            worldManager.setGlobalBlock(tileX, tileY, BlockType::Air);
        }
        else {
            worldManager.setGlobalWall(tileX, tileY, WallType::None);
        } 
    }
}

void Player::handleEvent(const sf::Event& event, sf::RenderWindow& window, WorldManager& worldManager) noexcept {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
        
        if (keyEvent->scancode == sf::Keyboard::Scancode::R) {
            if (m_buildMode == BuildModeType::Block) {
                m_buildMode = BuildModeType::Wall;
            } else if (m_buildMode == BuildModeType::Wall) {
                m_buildMode = BuildModeType::Block;
            }
        }
        if (keyEvent->scancode == sf::Keyboard::Scancode::LShift) {
            m_isSprinting = true;
        }
    }

    if (event.is<sf::Event::KeyReleased>()) {
        auto* keyEvent = event.getIf<sf::Event::KeyReleased>();
        
        if (keyEvent->scancode == sf::Keyboard::Scancode::LShift) {
            m_isSprinting = false;
        }
    }

    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            placeTile(window, worldManager);
        }
        if (mouseEvent->button == sf::Mouse::Button::Right) {
            breakTile(window, worldManager);
        }
    }
}

void Player::update(float deltaTime) noexcept {
    m_previousPosition = m_position; 

    sf::Vector2f direction{0.0f, 0.0f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) direction.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) direction.y += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) direction.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) direction.x += 1.0f;

    float length{std::hypot(direction.x, direction.y)};
    if (length > 0.0f) {
        direction /= length;
    }

    float currentSpeed = m_isSprinting ? (m_speed * 5.0f) : m_speed;

    m_position += direction * currentSpeed * deltaTime;
}

void Player::interpolate(float interpolationFactor) noexcept {
    m_visualPosition = m_previousPosition + 
        (m_position - m_previousPosition) * interpolationFactor;
}

void Player::draw(sf::RenderTarget& target) const {
    sf::RenderStates states;
    
    states.transform.translate(m_visualPosition);
    
    if (m_playerAtlas) {
        states.texture = m_playerAtlas;
    }

    target.draw(m_mesh, states);
}