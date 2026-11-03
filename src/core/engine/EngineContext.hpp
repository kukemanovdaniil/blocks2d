#pragma once

class Window;
class TextureLoader;
class UiManager;
class StateManager;
class PhysicManager;

struct EngineContext {
    Window& window;
    TextureLoader& textureLoader;
    UiManager& ui;
    StateManager& stateManager;
    PhysicManager& physicManager;
};
