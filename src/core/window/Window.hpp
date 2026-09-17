#pragma once

#include <SFML/Graphics.hpp>

class Window {
public:
    Window(unsigned int windowW, unsigned int windowH, const char* windowTitle, unsigned int windowFps);

    bool isOpen() const { return m_window.isOpen(); }
    void close() { m_window.close(); }
    
    std::optional<sf::Event> pollEvent() { return m_window.pollEvent(); }
    
    void clear(const sf::Color& color = sf::Color::Black) { m_window.clear(color); }
    void display() { m_window.display(); }

    sf::RenderWindow& getRenderWindow() { return m_window; }
    const sf::RenderWindow& getRenderWindow() const { return m_window; }

private: 
    unsigned int m_width;
    unsigned int m_height;
    
    const char* m_title;
    unsigned int m_fps;

    sf::RenderWindow m_window;
};