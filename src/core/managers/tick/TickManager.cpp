#include "TickManager.hpp"
#include <SFML/System/Time.hpp>

void TickManager::restart() noexcept {
    m_clock.restart();
    m_accumulator = 0.0f;
}

void TickManager::update() noexcept {
    float deltaTime = m_clock.restart().asSeconds();
    
    if (deltaTime > 1.0f) {
        deltaTime = 1.0f;
    }

    m_accumulator += deltaTime;
    m_lastDeltaTime = deltaTime;
}

bool TickManager::checkTick() noexcept {
    if (m_accumulator >= TIME_PER_TICK) {
        m_accumulator -= TIME_PER_TICK;
        return true;
    }
    return false;
}

float TickManager::getInterpolationFactor() const noexcept { 
    return m_accumulator / TIME_PER_TICK; 
}
