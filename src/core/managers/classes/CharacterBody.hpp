#pragma once
#include <box2d/box2d.h>
#include "src/core/managers/physic/collider/Collider.hpp"
#include <algorithm>
#include <cmath>

class CharacterBody : public Collider
{
public:
    CharacterBody() = default;
    virtual ~CharacterBody() override
    {
        if (b2Body_IsValid(m_bodyId))
        {
            b2DestroyBody(m_bodyId);
        }
    }

    void initCharacterPhysics(b2WorldId worldId, sf::Vector2f startPos, sf::Vector2f size) noexcept
    {
        m_size = size;

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = b2Vec2{startPos.x / 32.0f, startPos.y / 32.0f};
        bodyDef.fixedRotation = true;

        m_bodyId = b2CreateBody(worldId, &bodyDef);

        float skinRadius = 0.08f; 

        float halfWidth = (m_size.x / 64.0f) - skinRadius;
        float halfHeight = (m_size.y / 64.0f) - skinRadius;

        if (halfWidth < 0.01f) halfWidth = 0.01f;
        if (halfHeight < 0.01f) halfHeight = 0.01f;

        b2Polygon box = b2MakeRoundedBox(halfWidth, halfHeight, skinRadius);
    
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.material.friction = 0.0f;
        shapeDef.material.restitution = 0.0f;

        b2CreatePolygonShape(m_bodyId, &shapeDef, &box);
    }

    void updateCharacterPhysics(float dt, float inputDirX, bool wantsToJump, float maxSpeed) noexcept
    {
        if (!b2Body_IsValid(m_bodyId))
            return;

        b2Vec2 velocity = b2Body_GetLinearVelocity(m_bodyId);
        bool onGround = checkOnGround();

        if (inputDirX != 0.0f)
        {
            velocity.x = inputDirX * (maxSpeed / 32.0f);
        }
        else
        {
            float friction = onGround ? 20.0f : 2.0f;
            velocity.x -= velocity.x * friction * dt;
            if (std::abs(velocity.x) < 0.1f)
                velocity.x = 0.0f;
        }

        if (wantsToJump && onGround)
        {
            velocity.y = -18.0f;
        }

        b2Body_SetLinearVelocity(m_bodyId, velocity);
    }

    void setPosition(sf::Vector2f pos) noexcept
    {
        if (b2Body_IsValid(m_bodyId))
        {
            b2Body_SetTransform(m_bodyId, b2Vec2{pos.x / 32.0f, pos.y / 32.0f}, b2Rot_identity);
        }
    }

    [[nodiscard]] bool isOnGround() const noexcept
    {
        return checkOnGround();
    }

    void move(const sf::Vector2f &delta) noexcept override
    {
        if (!b2Body_IsValid(m_bodyId))
            return;
        b2Vec2 pos = b2Body_GetPosition(m_bodyId);
        b2Body_SetTransform(m_bodyId, b2Vec2{pos.x + delta.x / 32.0f, pos.y + delta.y / 32.0f}, b2Rot_identity);
    }

    [[nodiscard]] sf::Vector2f getPosition() const noexcept { return implPosition(); }
    [[nodiscard]] sf::Vector2f getPreviousPosition() const noexcept { return m_previousPosition; }
    void savePreviousPosition() noexcept { m_previousPosition = implPosition(); }
    void setSize(sf::Vector2f size) noexcept { m_size = size; }

    [[nodiscard]] sf::Vector2f implPosition() const noexcept override
    {
        if (!b2Body_IsValid(m_bodyId))
            return {0.f, 0.f};
        b2Vec2 pos = b2Body_GetPosition(m_bodyId);
        return sf::Vector2f(pos.x * 32.0f, pos.y * 32.0f);
    }

    [[nodiscard]] sf::Vector2f implSize() const noexcept override { return m_size; }

    [[nodiscard]] sf::Vector2f implVelocity() const noexcept override
    {
        if (!b2Body_IsValid(m_bodyId))
            return {0.f, 0.f};
        b2Vec2 vel = b2Body_GetLinearVelocity(m_bodyId);
        return sf::Vector2f(vel.x * 32.0f, vel.y * 32.0f);
    }

private:
    bool checkOnGround() const noexcept
    {
        if (!b2Body_IsValid(m_bodyId))
            return false;
        return std::abs(b2Body_GetLinearVelocity(m_bodyId).y) < 0.05f;
    }

    b2BodyId m_bodyId{b2_nullBodyId};
    sf::Vector2f m_previousPosition{0.0f, 0.0f};
    sf::Vector2f m_size{32.0f, 64.0f};
};
