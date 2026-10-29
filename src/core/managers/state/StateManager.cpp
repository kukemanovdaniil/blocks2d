// StateManager.cpp
#include "StateManager.hpp"
#include "State.hpp"

StateManager::~StateManager() {
}

void StateManager::changeState(std::unique_ptr<State> newState, EngineContext& context) {
    if (!m_states.empty()) {
        m_states.back()->cleanup(context);
        m_states.pop_back();
    }
    m_states.push_back(std::move(newState));
    m_states.back()->init(context);
}

void StateManager::pushState(std::unique_ptr<State> newState, EngineContext& context) {
    if (!m_states.empty()) {
        m_states.back()->pause(context);
    }
    m_states.push_back(std::move(newState));
    m_states.back()->init(context);
}

void StateManager::popState(EngineContext& context) {
    if (!m_states.empty()) {
        m_states.back()->cleanup(context);
        m_states.pop_back();
    }
    if (!m_states.empty()) {
        m_states.back()->resume(context);
    }
}

void StateManager::handleEvent(const sf::Event& event, EngineContext& context) {
    if (!m_states.empty()) m_states.back()->handleEvent(context, event);
}

void StateManager::updateTick(float tickTime, EngineContext& context) {
    if (!m_states.empty()) m_states.back()->updateTick(context, tickTime);
}

void StateManager::updateFrame(float deltaTime, float alpha, EngineContext& context) {
    if (!m_states.empty()) m_states.back()->updateFrame(context, deltaTime, alpha);
}

void StateManager::draw(EngineContext& context) {
    if (!m_states.empty()) m_states.back()->draw(context);
}
