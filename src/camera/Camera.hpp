#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera() = default;

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


    
    // OTHER

    void updateLerp(const sf::Vector2f target, float deltaTime) noexcept;

private:
    float m_zoom{1.0f};
    float m_currentZoom{1.0f};
    float m_lerp{9.0f};
    sf::Vector2f m_baseSize{1280, 720};

    sf::View m_view;
};
