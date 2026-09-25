#pragma once

#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float zoom, float lerp, sf::Vector2f baseSize);



    // GETTERS
    [[nodiscard]] float getZoom() const noexcept { return m_zoom; }
    [[nodiscard]] float getCurrentZoom() const noexcept { return m_currentZoom; }
    [[nodiscard]] float getLerp() const noexcept { return m_lerp; }
    [[nodiscard]] sf::Vector2f getBaseSize() const noexcept { return m_baseSize; }



    // SETTERS
    void setZoom(float zoom) noexcept { m_zoom = zoom; }
    void setLerp(float lerp) noexcept { m_lerp = lerp; }
    void setCenter(sf::Vector2f center) noexcept { m_view.setCenter(center); }
    void setSize(sf::Vector2f size) noexcept { m_view.setSize(size); }
    void setView(sf::RenderTarget& target) noexcept { target.setView(m_view); }
    void setBaseSize(sf::Vector2f baseSize) noexcept;


    
    // OTHER
    void updateLerp(const sf::Vector2f& target, float deltaTime) noexcept;
    
private:
    float m_zoom{1.0f};
    float m_currentZoom{1.0f};
    float m_lerp{1.0f};
    sf::Vector2f m_baseSize{0.0f, 0.0f};

    sf::View m_view;
};
