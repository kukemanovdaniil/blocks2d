#include <iostream>
#include <SFML/Graphics.hpp>
#include <print>
#include <optional>

#include "src/core/Config.hpp"
#include "src/core/tickManager/TickManager.hpp" 

#include "src/core/window/Window.hpp"

#include "src/player/Player.hpp"
#include "src/camera/Camera.hpp"
#include "src/worldManager/tileData/TileData.hpp"
#include "src/worldManager/WorldManager.hpp"

int main() {
    Window window(Config::defaultWindowSize, Config::title, Config::fps);
    window.toggleFullscreen();

    initBlockData();
    initWallData();

    TickManager tickManager;
    tickManager.restart(); 

    WorldManager worldManager;
    worldManager.loadAtlasTexture("res/textures/blockAtlas.png");
    worldManager.createWorld(10);

    Player player;
    Camera camera;
        
    float fpsTimer = 0.0f;
    int frameCount = 0;
    int currentFps = 0;

    while (window.isOpen()) {
        tickManager.update();
        float deltaTime = tickManager.getLastDeltaTime();

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0f) {
            currentFps = frameCount;
            frameCount = 0;
            fpsTimer = 0.0f;
            std::println("FPS: {}", currentFps);
        }

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

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

        float alpha = tickManager.getInterpolationFactor();
        player.interpolate(alpha);

        camera.updateLerp(player.getPosition(), deltaTime);

        window.clear(sf::Color{82, 176, 255, 255});

        camera.setView(window.getRenderWindow());

        worldManager.draw(window.getRenderWindow(), player, camera);

        player.draw(window.getRenderWindow());

        window.display();
    }

    return 0;
}
