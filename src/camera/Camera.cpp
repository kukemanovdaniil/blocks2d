#include "src/camera/Camera.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

Camera::Camera(float zoom, float lerp, sf::Vector2f baseSize)
    : m_zoom(zoom), m_lerp(lerp), m_baseSize(baseSize) {
        m_zoom = zoom;
        m_lerp = lerp;
        m_baseSize = baseSize;
}

void Camera::setZoom(float zoom) noexcept {
    m_zoom = zoom;
}

void Camera::updateLerp(sf::Vector2f target, float deltaTime) noexcept {
    sf::Vector2f currentCenter{m_view.getCenter()};
    float blend{1.0f - std::exp(-m_lerp * deltaTime)};

    float newX{std::lerp(currentCenter.x, target.x, blend)};
    float newY{std::lerp(currentCenter.y, target.y, blend)};
    m_view.setCenter({std::round(newX), std::round(newY)});

    m_currentZoom = std::lerp(m_currentZoom, m_zoom, blend);

    m_view.setSize(m_baseSize * m_currentZoom);
}