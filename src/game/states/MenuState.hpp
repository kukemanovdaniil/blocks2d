#pragma once

#include "src/core/managers/state/State.hpp"
#include <memory>

struct EngineContext;

class MenuState : public State {
public:
    MenuState() = default;
    ~MenuState() override = default;

    void init(EngineContext& context) override;
    void cleanup(EngineContext& context) override;

    void pause(EngineContext& context) override;
    void resume(EngineContext& context) override;

    void handleEvent(EngineContext& context, const sf::Event& event) override;
    void updateTick(EngineContext& context, float tickTime) override;
    void updateFrame(EngineContext& context, float deltaTime, float alpha) override;
    void draw(EngineContext& context) override;

private:
};
