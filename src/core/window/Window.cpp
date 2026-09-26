#include "Window.hpp"

#include "src/core/Config.hpp"

void Window::centerWindow() noexcept {
    sf::Vector2u screenSize = Config::DEFAULT_WINDOW_SIZE;

    sf::Vector2i centerPos(
        static_cast<int>((screenSize.x - m_size.x) / 2),
        static_cast<int>((screenSize.y - m_size.y) / 2)
    );
    
    m_window.setPosition(centerPos);
}

Window::Window(sf::Vector2u size, const char* title, unsigned int fps)
    : m_size(size), m_title(title), m_fps(fps), m_window(sf::VideoMode(size), title) {
    m_window.setFramerateLimit(fps);
    m_window.setMinimumSize(Config::MIN_WINDOW_SIZE);
    centerWindow();
}

void Window::toggleFullscreen() noexcept {
    if (!m_isFullscreen) {
        m_previousPos = m_window.getPosition();
        m_previousSize = m_window.getSize();
    }

    m_isFullscreen = !m_isFullscreen;

    if (m_isFullscreen) {
        m_window.create(
            sf::VideoMode(Config::getScreenSize()),
            m_title, 
            sf::State::Fullscreen
        );
    } else {
        m_window.create(
            sf::VideoMode(m_previousSize),
            m_title, 
            sf::State::Windowed
        );
        m_window.setPosition(m_previousPos);
        m_window.setMinimumSize(Config::MIN_WINDOW_SIZE);
    }

    m_window.setFramerateLimit(m_fps);
}