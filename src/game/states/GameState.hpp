#pragma once

#include "src/core/managers/state/State.hpp"
#include "src/game/player/Player.hpp"
#include "src/game/camera/Camera.hpp"
#include "src/game/worldManager/WorldManager.hpp"
#include <memory>

struct EngineContext;

class GameState : public State {
public:
    GameState() = default;
    ~GameState() override = default;

    void init(EngineContext& context) override;
    void cleanup(EngineContext& context) override;

    void pause(EngineContext& context) override;
    void resume(EngineContext& context) override;

    void handleEvent(EngineContext& context, const sf::Event& event) override;
    void updateTick(EngineContext& context, float tickTime) override;
    void updateFrame(EngineContext& context, float deltaTime, float alpha) override;
    void draw(EngineContext& context) override;

private:
    WorldManager m_worldManager;
    Player m_player;
    std::unique_ptr<Camera> m_camera;
};
