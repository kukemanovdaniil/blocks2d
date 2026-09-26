#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <expected>
#include <string>
#include <filesystem>

class UiManager {
public:
    UiManager() noexcept;
    ~UiManager();

    UiManager(const UiManager&) = delete;
    UiManager& operator=(const UiManager&) = delete;

    std::expected<void, std::string> init(sf::RenderWindow& window);

    void handleEvent(const sf::RenderWindow& window, const sf::Event& event) noexcept;

    void beginFrame(sf::RenderWindow& window) noexcept;

    void endFrame(sf::RenderWindow& window) noexcept;

private:
    sf::Clock m_deltaClock;
    bool m_isInitialized{false};

    std::string m_iniFilePath; 

    void applyCustomTheme() noexcept;
};
