#pragma once 

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

namespace Config {
    // CONSTANS
    inline constexpr const char* windowTitle = "blocks2d";

    inline constexpr unsigned int windowFps = 60;

    inline constexpr unsigned int defaultWindowW = 1280;
    inline constexpr unsigned int defaultWindowH = 720;

    // GETTERS
    inline unsigned int getScreenW() noexcept { return sf::VideoMode::getDesktopMode().size.x; }
    inline unsigned int getScreenH() noexcept { return sf::VideoMode::getDesktopMode().size.y; }
}
