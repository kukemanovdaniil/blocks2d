#pragma once
#include <SFML/System/Clock.hpp>

class TickManager {
public:
    TickManager() = default;

    void restart() noexcept;
    void update() noexcept;
    
    bool checkTick() noexcept;

    constexpr float getTimePerTick() const noexcept { return TIME_PER_TICK; }
    float getLastDeltaTime() const noexcept { return m_lastDeltaTime; }
    float getInterpolationFactor() const noexcept;

private:
    sf::Clock m_clock;
    float m_accumulator{0.0f};
    float m_lastDeltaTime{0.0f};

    static constexpr float TIME_PER_TICK = 1.0f / 20.0f; 
};
