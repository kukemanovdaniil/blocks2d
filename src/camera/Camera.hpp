#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float zoom, float lerp, sf::Vector2f baseSize);

    // GETTERS

    float getZoom() const noexcept { return m_zoom; }
    float getCurrentZoom() const noexcept { return m_currentZoom; }
    float getLerp() const noexcept { return m_lerp; }
    sf::Vector2f getBaseSize() const noexcept { return m_baseSize; }



    // SETTERS

    void setZoom(float zoom) noexcept;
    void setLerp(float lerp) noexcept { m_lerp = lerp; }
    void setCenter(const sf::Vector2f center) noexcept { m_view.setCenter(center); }
    void setSize(const sf::Vector2f size) { m_view.setSize(size); }
    void setView(sf::RenderTarget& target) noexcept { target.setView(m_view); }
    void setBaseSize(sf::Vector2f baseSize) noexcept { m_baseSize = baseSize; }


    
    // OTHER

    void updateLerp(const sf::Vector2f target, float deltaTime) noexcept;

private:
    float m_zoom;
    float m_currentZoom;
    float m_lerp;
    sf::Vector2f m_baseSize;

    sf::View m_view;
};
