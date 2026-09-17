#pragma once 
#include <SFML/Window/VideoMode.hpp>

namespace Config {
    // CONSTANS
    inline constexpr const char* windowTitle = "blocks2d";

    inline constexpr unsigned int windowFps = 60;

    inline constexpr unsigned int defaultWindowW = 1280;
    inline constexpr unsigned int defaultWindowH = 720;

    // GETTERS
    unsigned int getScreenW() noexcept;
    unsigned int getScreenH() noexcept;   
}
