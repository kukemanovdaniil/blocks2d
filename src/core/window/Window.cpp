#include "Window.hpp"

#include "src/core/Config.hpp"

void Window::centerWindow() noexcept {
    unsigned int screenW = Config::getScreenW();
    unsigned int screenH = Config::getScreenH();
    
    sf::Vector2i centerPosition(
        static_cast<int>((screenW - m_width) / 2),
        static_cast<int>((screenH - m_height) / 2)
    );
    
    m_window.setPosition(centerPosition);
}

Window::Window(unsigned int width, unsigned int height, const char* title, unsigned int fps)
    : m_width(width), m_height(height), m_title(title), m_fps(fps), m_window(sf::VideoMode({width, height}), title) {
    m_window.setFramerateLimit(fps);
    centerWindow();
}

void Window::toggleFullscreen() noexcept {
    m_isFullscreen = !m_isFullscreen;

    if (m_isFullscreen) {
        m_window.create(
            sf::VideoMode({Config::getScreenW(), Config::getScreenH()}), 
            m_title, 
            sf::State::Fullscreen
        );
    } else {
        m_window.create(
            sf::VideoMode({m_width, m_height}), 
            m_title, 
            sf::State::Windowed
        );
        centerWindow();
    }

    m_window.setFramerateLimit(m_fps);
}