#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class State;
struct EngineContext;

class StateManager {
public:
    StateManager() = default;
    ~StateManager();

    void changeState(std::unique_ptr<State> newState, EngineContext& context);
    void pushState(std::unique_ptr<State> newState, EngineContext& context);
    void popState(EngineContext& context);

    void handleEvent(const sf::Event& event, EngineContext& context);
    void updateTick(float tickTime, EngineContext& context);
    void updateFrame(float deltaTime, float alpha, EngineContext& context);
    void draw(EngineContext& context);

    bool isEmpty() const { return m_states.empty(); }

private:
    std::vector<std::unique_ptr<State>> m_states;
};
