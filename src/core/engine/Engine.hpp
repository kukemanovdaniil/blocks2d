#pragma once

#include "src/core/window/Window.hpp"
#include "src/core/loaders/textureLoader/TextureLoader.hpp"
#include "src/core/managers/ui/UiManager.hpp"
#include "src/core/managers/tick/TickManager.hpp"
#include "src/core/managers/state/StateManager.hpp"
#include "src/core/engine/EngineContext.hpp"

#include <memory>

class Engine {
public:
    Engine();
    ~Engine() = default;

    bool init();
    
    void run();

private:
    Window m_window;
    TextureLoader m_textureLoader;
    UiManager m_ui;
    StateManager m_stateManager;
    TickManager m_tickManager;

    std::unique_ptr<EngineContext> m_context;

    void processEvents();
    void update(float deltaTime, float alpha);
    void render();
};
