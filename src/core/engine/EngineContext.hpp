#pragma once

class Window;
class TextureLoader;
class UiManager;
class StateManager;

struct EngineContext {
    Window& window;
    TextureLoader& textureLoader;
    UiManager& ui;
    StateManager& stateManager;
};
