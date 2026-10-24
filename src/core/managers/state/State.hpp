#pragma once

class StateManager;

class State {
public:
    virtual ~State() = default;

    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() {}
    virtual void resume() {}

    virtual void handleEvents(StateManager& manager) = 0;
    virtual void update(StateManager& manager, float dt) = 0;
    virtual void draw(StateManager& manager) = 0;
};
