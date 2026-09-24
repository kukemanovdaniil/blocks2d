#pragma once 

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

#include "CMakeConfig.hpp"

namespace Config {
    // CONSTANS
    inline constexpr unsigned int MAX_FPS{60};

    inline constexpr sf::Vector2u DEFAULT_WINDOW_SIZE{1280, 720};

    // GETTERS
    
    [[nodiscard]] inline sf::Vector2u getScreenSize() noexcept { return sf::VideoMode::getDesktopMode().size; }
}
