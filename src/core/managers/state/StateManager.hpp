#pragma once

#include <vector>
#include <memory>
#include "State.hpp"

class StateManager {
public:
    StateManager() = default;
    ~StateManager();

    void init();
    void cleanup();
    
    void changeState(std::unique_ptr<State> newState);
    
    void pushState(std::unique_ptr<State> newState);
    
    void popState();

    void handleEvents();
    void update(float dt);
    void draw();

    bool running() const { return m_running; }
    void quit() { m_running = false; }

private:
    std::vector<std::unique_ptr<State>> m_states;
    bool m_running = true;
};
