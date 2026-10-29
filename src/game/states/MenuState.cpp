#include "MenuState.hpp"

#include <iostream>
#include <imgui.h>

#include "src/core/managers/state/StateManager.hpp"
#include "src/core/window/Window.hpp"
#include "src/core/managers/ui/UiManager.hpp"
#include "src/core/Config.hpp"
#include "src/core/engine/EngineContext.hpp"

#include "src/game/states/GameState.hpp" 

void MenuState::init(EngineContext& /*context*/) {
}

void MenuState::cleanup(EngineContext& /*context*/) {
}

void MenuState::pause(EngineContext& /*context*/) {
}

void MenuState::resume(EngineContext& /*context*/) {
}

void MenuState::handleEvent(EngineContext& /*context*/, const sf::Event& /*event*/) {
}

void MenuState::updateTick(EngineContext& /*context*/, float /*tickTime*/) {
}

void MenuState::updateFrame(EngineContext& /*context*/, float /*deltaTime*/, float /*alpha*/) {
}

void MenuState::draw(EngineContext& context) {
    auto& targetWindow = context.window.getRenderWindow();
    auto& ui = context.ui;

    // ==========================================
    // SCREEN
    // ==========================================
    context.window.clear(sf::Color{30, 30, 40, 255});

    // ==========================================
    // UI
    // ==========================================
    ui.beginFrame(targetWindow);

    sf::Vector2u windowSize = targetWindow.getSize();
    ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2.0f, windowSize.y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(250, 200), ImGuiCond_Always);

    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Spacing();

    float textWidth = ImGui::CalcTextSize(Config::FULL_TITLE).x;
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - textWidth) * 0.5f);
    
    ImGui::Text(Config::FULL_TITLE);
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("play", ImVec2(-1, 40))) {
        context.stateManager.changeState(std::make_unique<GameState>(), context);
    }

    ImGui::Spacing();

    if (ImGui::Button("exit", ImVec2(-1, 40))) {
        context.window.close();
    }

    ImGui::End();

    ui.endFrame(targetWindow);
}
