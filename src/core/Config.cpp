#include "src/core/Config.hpp"

unsigned int Config::getScreenH() noexcept {
    return sf::VideoMode::getDesktopMode().size.y;
}

unsigned int Config::getScreenW() noexcept {
    return sf::VideoMode::getDesktopMode().size.x;
}