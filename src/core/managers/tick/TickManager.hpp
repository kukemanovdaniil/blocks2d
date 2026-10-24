#pragma once
#include <SFML/System/Clock.hpp>

class TickManager {
public:
    TickManager() = default;

    // GETTERS

    [[nodiscard]] constexpr float getTimePerTick() const noexcept { return TIME_PER_TICK; }
    [[nodiscard]] float getLastDeltaTime() const noexcept { return m_lastDeltaTime; }
    [[nodiscard]] float getInterpolationFactor() const noexcept;

    // OTHER

    void restart() noexcept;
    void update() noexcept;
    
    bool checkTick() noexcept;

private:
    sf::Clock m_clock;
    float m_accumulator{0.0f};
    float m_lastDeltaTime{0.0f};

    static constexpr float TIME_PER_TICK{1.0f / 40.0f}; 
};
