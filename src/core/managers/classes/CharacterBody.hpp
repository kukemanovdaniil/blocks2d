#pragma once
#include "src/core/managers/physic/collider/Collider.hpp"
#include <algorithm>
#include <cmath>

class CharacterBody : public Collider {
public:
    CharacterBody() = default;
    virtual ~CharacterBody() override = default;

    [[nodiscard]] sf::Vector2f implPosition() const noexcept override { return m_position; }
    [[nodiscard]] sf::Vector2f implSize() const noexcept override { return m_size; }
    [[nodiscard]] sf::Vector2f implVelocity() const noexcept override { return m_velocity; }
    
    void move(const sf::Vector2f& delta) noexcept override { m_position += delta; }
    
    void onCollision(Collider& /*other*/, const sf::Vector2f& normal) override {
        // ПОЛ / ПОТОЛОК
        if (normal.y < 0.0f) {
            m_onGround = true; 
            m_velocity.y = 0.0f;
        }
        if (normal.y > 0.0f) {
            m_velocity.y = 0.0f;
        }

        if (std::abs(normal.x) > 0.0f) {
            m_velocity.x = 0.0f; 
        }
    }

    void updatePhysics(float dt, float inputDirX, bool wantsToJump, float maxSpeed) noexcept {
        m_previousPosition = m_position;

        constexpr float ACCEL_AIR = 1800.0f;
        constexpr float FRICTION_GROUND = 25.0f;
        constexpr float DRAG_AIR = 0.5f;
        constexpr float GRAVITY = 1600.0f;      
        constexpr float MAX_FALL_SPEED = 900.0f;
        constexpr float JUMP_IMPULSE = -550.0f;

        if (m_onGround) {
            if (inputDirX != 0.0f) {
                m_velocity.x = inputDirX * maxSpeed;
            } else {
                m_velocity.x -= m_velocity.x * FRICTION_GROUND * dt;
                if (std::abs(m_velocity.x) < 10.0f) m_velocity.x = 0.0f;
            }
        } 
        else {
            if (inputDirX != 0.0f) {
                m_velocity.x += inputDirX * ACCEL_AIR * dt;
                float maxAirSpeed = maxSpeed * 1.2f; 
                m_velocity.x = std::clamp(m_velocity.x, -maxAirSpeed, maxAirSpeed);
            } else {
                m_velocity.x -= m_velocity.x * DRAG_AIR * dt;
            }
        }

        if (wantsToJump && m_onGround) {
            m_velocity.y = JUMP_IMPULSE;
            m_onGround = false;
        }

        m_velocity.y += GRAVITY * dt;
        if (m_velocity.y > MAX_FALL_SPEED) m_velocity.y = MAX_FALL_SPEED;

        m_onGround = false; 
    }

    [[nodiscard]] sf::Vector2f getPosition() const noexcept { return m_position; }
    [[nodiscard]] sf::Vector2f getPreviousPosition() const noexcept { return m_previousPosition; }
    [[nodiscard]] sf::Vector2f& getVelocity() noexcept { return m_velocity; }
    [[nodiscard]] bool isOnGround() const noexcept { return m_onGround; }
    
    void setPosition(sf::Vector2f pos) noexcept { m_position = pos; }
    void setSize(sf::Vector2f size) noexcept { m_size = size; }

protected:
    sf::Vector2f m_previousPosition{0.0f, 0.0f};
    sf::Vector2f m_position{100.0f, 100.0f};
    sf::Vector2f m_velocity{0.0f, 0.0f};
    sf::Vector2f m_size{24.0f, 64.0f};
    bool m_onGround{false};
};
