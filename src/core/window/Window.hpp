#pragma once

#include <SFML/Graphics.hpp>



class Window {
public:
    Window(sf::Vector2u size, const char* title, unsigned int fps);

    bool isOpen() const { return m_window.isOpen(); }
    void close() { m_window.close(); }
    
    std::optional<sf::Event> pollEvent() { return m_window.pollEvent(); }
    
    void clear(const sf::Color& color = sf::Color::Black) { m_window.clear(color); }
    void display() { m_window.display(); }

    void toggleFullscreen() noexcept;
    bool isFullscreen() const noexcept { return m_isFullscreen; }

    sf::RenderWindow& getRenderWindow() { return m_window; }
    const sf::RenderWindow& getRenderWindow() const { return m_window; }

private: 
    sf::Vector2u m_size;
    sf::Vector2u m_previousSize;
    sf::Vector2i m_previousPos;
    
    const char* m_title;
    unsigned int m_fps;

    bool m_isFullscreen = false;

    sf::RenderWindow m_window;

    void centerWindow() noexcept; 
};