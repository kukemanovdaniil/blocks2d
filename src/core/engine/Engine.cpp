#include "Engine.hpp"
#include "src/core/Config.hpp"
#include "src/game/states/GameState.hpp"
#include "src/game/states/MenuState.hpp"
#include <iostream>

Engine::Engine() 
    : m_window(Config::DEFAULT_WINDOW_SIZE, Config::FULL_TITLE, Config::MAX_FPS) 
{
}

bool Engine::init() {
    if (auto uiInit = m_ui.init(m_window.getRenderWindow()); !uiInit) {
        std::cerr << "Engine UI error : " << uiInit.error() << std::endl;
        return false;
    }

    m_context = std::make_unique<EngineContext>(
        m_window,
        m_textureLoader,
        m_ui,
        m_stateManager
    );

    m_stateManager.changeState(std::make_unique<MenuState>(), *m_context);

    return true;
}

void Engine::run() {
    m_tickManager.restart();

    while (m_window.isOpen()) {
        m_tickManager.update();

        processEvents();
        
        while (m_tickManager.checkTick()) {
            m_stateManager.updateTick(m_tickManager.getTimePerTick(), *m_context);
        }

        update(m_tickManager.getLastDeltaTime(), m_tickManager.getInterpolationFactor());
        render();
    }
}

void Engine::processEvents() {
    while (const std::optional<sf::Event> event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (const auto* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressedEvent->code == sf::Keyboard::Key::F8) m_window.close();
            if (keyPressedEvent->code == sf::Keyboard::Key::F11) m_window.toggleFullscreen();
        }

        m_ui.handleEvent(m_window.getRenderWindow(), *event);
        m_stateManager.handleEvent(*event, *m_context);
    }
}

void Engine::update(float deltaTime, float alpha) {
    m_stateManager.updateFrame(deltaTime, alpha, *m_context);
}

void Engine::render() {
    m_stateManager.draw(*m_context);
    m_window.display();
}
