#pragma once 

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

namespace Config {
    // CONSTANS
    inline constexpr const char* title = "blocks2d";

    inline constexpr unsigned int fps = 60;

    inline constexpr sf::Vector2u defaultWindowSize = {1280, 720};

    // GETTERS
    inline sf::Vector2u getScreenSize() noexcept { return sf::VideoMode::getDesktopMode().size; }
}
