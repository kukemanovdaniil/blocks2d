#include "src/game/states/GameState.hpp"

#include <iostream>
#include <imgui.h>

#include "src/core/managers/state/StateManager.hpp"
#include "src/core/window/Window.hpp"
#include "src/core/managers/ui/UiManager.hpp"
#include "src/core/loaders/textureLoader/TextureLoader.hpp"
#include "src/core/Config.hpp"
#include "src/game/worldManager/tileData/TileData.hpp"
#include "src/core/engine/EngineContext.hpp"

void GameState::init(EngineContext& context) {
    auto& targetWindow = context.window.getRenderWindow();
    auto& loader = context.textureLoader;

    const sf::Texture& blocksAtlas = loader.get("res/textures/blocksAtlas.png");
    const sf::Texture& playerAtlas = loader.get("res/textures/playerAtlas.png");

    initBlockData();
    initWallData();

    m_worldManager.setAtlasTexture(blocksAtlas);
    m_worldManager.createWorld(25);

    m_player.setAtlasTexture(playerAtlas);

    m_camera = std::make_unique<Camera>(
        1.0f, 
        9.0f, 
        sf::Vector2f(Config::getCurrentScreenWindow(targetWindow))
    );
}

void GameState::cleanup(EngineContext& context) {
}

void GameState::pause(EngineContext& context) {
}

void GameState::resume(EngineContext& context) {
}

void GameState::handleEvent(EngineContext& context, const sf::Event& event) {
    auto& targetWindow = context.window.getRenderWindow();

    if (event.is<sf::Event::Resized>()) {
        m_camera->setBaseSize(sf::Vector2f(Config::getCurrentScreenWindow(targetWindow)));
    }

    if (const auto* scrollEvent = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (scrollEvent->wheel == sf::Mouse::Wheel::Vertical) {
            float zoomFactor = 1.0f - (scrollEvent->delta * 0.1f); 
            m_camera->setZoom(m_camera->getZoom() * zoomFactor);
        }
    }

    m_player.handleEvent(event, targetWindow, m_worldManager);
}

void GameState::updateTick(EngineContext& context, float tickTime) {
    m_player.update(tickTime);
}

void GameState::updateFrame(EngineContext& context, float deltaTime, float alpha) {
    m_player.interpolate(alpha);
    m_camera->updateLerp(m_player.getVisualPosition(), deltaTime);
}

void GameState::draw(EngineContext& context) {
    auto& targetWindow = context.window.getRenderWindow();
    auto& ui = context.ui;

    // ==========================================
    // SCREEN
    // ==========================================
    context.window.clear(sf::Color{138, 235, 241, 255});

    // ==========================================
    // WORLD
    // ==========================================
    m_camera->setView(targetWindow);
    m_worldManager.draw(targetWindow, m_player, *m_camera);
    m_player.draw(targetWindow);

    // ==========================================
    // UI
    // ==========================================
    ui.beginFrame(targetWindow);

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::Begin("HUD", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
    
    ImGui::Text(Config::FULL_TITLE);
    ImGui::Separator();
    ImGui::Text("FPS: %u", static_cast<unsigned int>(ImGui::GetIO().Framerate));
    ImGui::Text("Resolution: %u x %u", targetWindow.getSize().x, targetWindow.getSize().y);

    int positionX = static_cast<int>(m_player.getPosition().x / TILE_SIZE);
    int positionY = static_cast<int>((m_player.getPosition().y + m_player.getSize().y / 2.0f) / TILE_SIZE);
    ImGui::Text("Position: %i x %i", positionX, positionY);
    
    ImGui::End();

    ui.endFrame(targetWindow);
}
