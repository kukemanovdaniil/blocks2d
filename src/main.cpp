#include <iostream>
#include <SFML/Graphics.hpp>
#include <print>
#include <optional>

#include "src/core/Config.hpp"
#include "src/core/tick/TickManager.hpp" 

#include "src/core/window/Window.hpp"
#include "src/core/ui/uiManager.hpp"
#include <imgui.h>

#include "src/player/Player.hpp"
#include "src/camera/Camera.hpp"
#include "src/worldManager/tileData/TileData.hpp"
#include "src/worldManager/WorldManager.hpp"

int main() {
    Window window(Config::defaultWindowSize, Config::fullTitle, Config::fps);
    window.toggleFullscreen();

    UiManager ui;
    if (auto uiInit = ui.init(window.getRenderWindow()); !uiInit) {
        std::cerr << "ui error : " << uiInit.error() << std::endl;
        return -1;
    }

    initBlockData();
    initWallData();

    TickManager tickManager;
    tickManager.restart(); 

    WorldManager worldManager;
    worldManager.loadAtlasTexture("res/textures/blockAtlas.png");
    worldManager.createWorld(10);

    Player player;
    Camera camera;

    while (window.isOpen()) {
        tickManager.update();
        float deltaTime = tickManager.getLastDeltaTime();

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            ui.handleEvent(window.getRenderWindow(), *event);

            if (const auto* scrollEvent = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (scrollEvent->wheel == sf::Mouse::Wheel::Vertical) {
            
                float zoomFactor = 1.0f - (scrollEvent->delta * 0.1f); 
            
                camera.setZoom(camera.getZoom() * zoomFactor);
            }
        }

            if (const auto* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressedEvent->code == sf::Keyboard::Key::F8) {
                    window.close();
                }
                if (keyPressedEvent->code == sf::Keyboard::Key::F11) {
                    window.toggleFullscreen();
                }
            }
            player.handleEvent(*event, window.getRenderWindow(), worldManager);
        }

        while (tickManager.checkTick()) {
            player.update(tickManager.getTimePerTick());
        }



        // ==========================================
        // RENDER UI
        // ==========================================

        ui.beginFrame(window.getRenderWindow());

        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::Begin("HUD", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
        ImGui::Text(Config::fullTitle);
        ImGui::Separator();
        ImGui::Text("FPS: %u", static_cast<unsigned int>(ImGui::GetIO().Framerate));
        ImGui::Text("Resolution: %u x %u", window.getRenderWindow().getSize().x, window.getRenderWindow().getSize().y);

        int positionX = static_cast<int>(player.getPosition().x / TILE_SIZE);
        int positionY = static_cast<int>(player.getPosition().y / TILE_SIZE);

        ImGui::Text("Position: %i x %i", positionX, positionY);
        ImGui::End();



        // ==========================================
        // RENDER
        // ==========================================

        float alpha = tickManager.getInterpolationFactor();
        player.interpolate(alpha);

        camera.updateLerp(player.getPosition() - sf::Vector2f{0.0, 16.0}, deltaTime);

        window.clear(sf::Color{82, 176, 255, 255});

        camera.setView(window.getRenderWindow());

        worldManager.draw(window.getRenderWindow(), player, camera);

        player.draw(window.getRenderWindow());

        ui.endFrame(window.getRenderWindow());

        window.display();
    }

    return 0;
}
