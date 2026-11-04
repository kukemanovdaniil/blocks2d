#pragma once
#include <SFML/System/Vector2.hpp>
#include <utility>

enum class ColliderType : char {
    StaticBlock,
    DynamicEntity,
    MovingPlatform
};

class Collider {
public:
    virtual ~Collider() = default;

    template <typename Self>
    [[nodiscard]] constexpr auto getPosition(this Self&& self) noexcept -> decltype(auto) {
        return std::forward<Self>(self).implPosition();
    }

    template <typename Self>
    [[nodiscard]] constexpr auto getSize(this Self&& self) noexcept -> decltype(auto) {
        return std::forward<Self>(self).implSize();
    }

    template <typename Self>
    [[nodiscard]] constexpr auto getVelocity(this Self&& self) noexcept -> decltype(auto) {
        return std::forward<Self>(self).implVelocity();
    }

    [[nodiscard]] virtual ColliderType getType() const noexcept = 0;

    virtual void move(const sf::Vector2f& delta) noexcept = 0;

protected:
    [[nodiscard]] virtual sf::Vector2f implPosition() const noexcept = 0;
    [[nodiscard]] virtual sf::Vector2f implSize() const noexcept = 0;
    [[nodiscard]] virtual sf::Vector2f implVelocity() const noexcept = 0;
};
