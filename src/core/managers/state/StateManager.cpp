#include "StateManager.hpp"

void StateManager::init() {
    m_running = true;
}

void StateManager::cleanup() {
    while (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
    }
}

void StateManager::changeState(std::unique_ptr<State> newState) {
    if (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
    }

    m_states.push_back(std::move(newState));
    m_states.back()->init();
}

void StateManager::pushState(std::unique_ptr<State> newState) {
    if (!m_states.empty()) {
        m_states.back()->pause();
    }

    m_states.push_back(std::move(newState));
    m_states.back()->init();
}

void StateManager::popState() {
    if (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
    }

    if (!m_states.empty()) {
        m_states.back()->resume();
    }
}

void StateManager::handleEvents() {
    if (!m_states.empty()) {
        m_states.back()->handleEvents(*this);
    }
}

void StateManager::update(float dt) {
    if (!m_states.empty()) {
        m_states.back()->update(*this, dt);
    }
}

void StateManager::draw() {
    if (!m_states.empty()) {
        m_states.back()->draw(*this);
    }
}
