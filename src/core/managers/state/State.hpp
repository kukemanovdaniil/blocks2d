#pragma once
#include <SFML/Graphics.hpp>

struct EngineContext;

class State {
public:
    virtual ~State() = default;

    virtual void init(EngineContext& context) = 0;
    virtual void cleanup(EngineContext& context) = 0;

    virtual void pause(EngineContext& context) {}
    virtual void resume(EngineContext& context) {}

    virtual void handleEvent(EngineContext& context, const sf::Event& event) = 0;
    virtual void updateTick(EngineContext& context, float tickTime) = 0;
    virtual void updateFrame(EngineContext& context, float deltaTime, float alpha) = 0;
    virtual void draw(EngineContext& context) = 0;
};
