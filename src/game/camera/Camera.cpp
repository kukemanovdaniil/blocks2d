#include "Camera.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

Camera::Camera(float zoom, float lerp, sf::Vector2f baseSize)
    : m_zoom(zoom), m_lerp(lerp), m_baseSize(baseSize) {
        m_zoom = zoom;
        m_lerp = lerp;
        m_baseSize = baseSize;
        m_view.setSize(m_baseSize * m_currentZoom);
}

void Camera::setBaseSize(sf::Vector2f baseSize) noexcept { 
    m_baseSize = baseSize; 
    m_view.setSize(m_baseSize * m_currentZoom);
}

void Camera::updateLerp(const sf::Vector2f& target, float deltaTime) noexcept {
    sf::Vector2f currentCenter{m_view.getCenter()};
    float blend{1.0f - std::exp(-m_lerp * deltaTime)};

    float newX{std::lerp(currentCenter.x, target.x, blend)};
    float newY{std::lerp(currentCenter.y, target.y, blend)};
    m_view.setCenter({newX, newY});

    m_currentZoom = std::lerp(m_currentZoom, m_zoom, blend);

    m_view.setSize(m_baseSize * m_currentZoom);
}