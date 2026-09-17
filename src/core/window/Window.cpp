#include "Window.hpp"

Window::Window(unsigned int width, unsigned int height, const char* title, unsigned int fps)
    : m_width(width), m_height(height), m_title(title), m_fps(fps), m_window(sf::VideoMode({width, height}), title) {
    m_window.setFramerateLimit(fps);
}

