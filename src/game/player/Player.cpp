#include "Player.hpp"
#include "src/game/worldManager/WorldManager.hpp"
#include <cmath>

Player::Player() {
    m_mesh.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_mesh.resize(6);

    setSize(PHYSICS_SIZE);

    float posX0 = 0.0f;
    float posX1 = SIZE.x;
    float posY0 = 0.0f;
    float posY1 = SIZE.y;

    float texX0 = 0.0f;
    float texX1 = TEX_SIZE.x;
    float texY0 = 0.0f;
    float texY1 = TEX_SIZE.y;

    m_mesh[0].position = sf::Vector2f(posX0, posY0);
    m_mesh[1].position = sf::Vector2f(posX0, posY1);
    m_mesh[2].position = sf::Vector2f(posX1, posY0);
    m_mesh[3].position = sf::Vector2f(posX0, posY1);
    m_mesh[4].position = sf::Vector2f(posX1, posY1);
    m_mesh[5].position = sf::Vector2f(posX1, posY0);

    m_mesh[0].texCoords = sf::Vector2f{texX0, texY0};
    m_mesh[1].texCoords = sf::Vector2f{texX0, texY1};
    m_mesh[2].texCoords = sf::Vector2f{texX1, texY0};
    m_mesh[3].texCoords = sf::Vector2f{texX0, texY1};
    m_mesh[4].texCoords = sf::Vector2f{texX1, texY1};
    m_mesh[5].texCoords = sf::Vector2f{texX1, texY0};
}

void Player::modifyTileAtMouse(sf::RenderWindow& window, WorldManager& worldManager, bool isPlacing) noexcept {
    if (m_buildMode != BuildModeType::Block && m_buildMode != BuildModeType::Wall) return;

    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    int tileX = static_cast<int>(std::floor(worldPos.x / 32.0f));
    int tileY = static_cast<int>(std::floor(worldPos.y / 32.0f));

    if (m_buildMode == BuildModeType::Block) {
        worldManager.setGlobalBlock(tileX, tileY, isPlacing ? BlockType::Limestone : BlockType::Air);
    } else {
        worldManager.setGlobalWall(tileX, tileY, isPlacing ? WallType::Limestone : WallType::None);
    }
}

void Player::handleEvent(const sf::Event& event, sf::RenderWindow& window, WorldManager& worldManager) noexcept {
    if (event.is<sf::Event::KeyPressed>()) {
        auto scancode = event.getIf<sf::Event::KeyPressed>()->scancode;
        if (scancode == sf::Keyboard::Scancode::R) {
            m_buildMode = (m_buildMode == BuildModeType::Block) ? BuildModeType::Wall : BuildModeType::Block;
        }
        if (scancode == sf::Keyboard::Scancode::LShift) m_isSprinting = true;
    }

    if (event.is<sf::Event::KeyReleased>()) {
        if (event.getIf<sf::Event::KeyReleased>()->scancode == sf::Keyboard::Scancode::LShift) {
            m_isSprinting = false;
        }
    }

    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto button = event.getIf<sf::Event::MouseButtonPressed>()->button;
        if (button == sf::Mouse::Button::Left)  modifyTileAtMouse(window, worldManager, true);
        if (button == sf::Mouse::Button::Right) modifyTileAtMouse(window, worldManager, false);
    }
}

void Player::update(float deltaTime) noexcept {
    float inputDirX = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) inputDirX -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) inputDirX += 1.0f;

    bool wantsToJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space);
    float currentMaxSpeed = m_isSprinting ? (m_speed * 1.5f) : m_speed;

    CharacterBody::updatePhysics(deltaTime, inputDirX, wantsToJump, currentMaxSpeed);
}

void Player::interpolate(float interpolationFactor) noexcept {
    m_visualPosition = getPreviousPosition() + (getPosition() - getPreviousPosition()) * interpolationFactor;
}

void Player::draw(sf::RenderTarget& target) const {
    sf::RenderStates states;
    states.transform.translate(m_visualPosition);
    if (m_playerAtlas) states.texture = m_playerAtlas;
    target.draw(m_mesh, states);
}
