#pragma once

#include <unordered_map>
#include "src/game/worldManager/chunk/Chunk.hpp"
#include "src/game/camera/Camera.hpp"
#include <print>
#include <SFML/OpenGL.hpp>
#include "src/core/Config.hpp"
#include "src/core/math/Math.hpp"
#include <cmath>

class Player;

class WorldManager {
public:
    void createWorld(int size);
    


    // GETTERS
    [[nodiscard]] WallType getGlobalWall(int blockX, int blockY);
    [[nodiscard]] BlockType getGlobalBlock(int blockX, int blockY);
    [[nodiscard]] BlockType getGlobalBlockInPixels(float globalX, float globalY);



    // SETTERS
    bool setGlobalBlock(int blockX, int blockY, BlockType type);
    bool setGlobalWall(int blockX, int blockY, WallType type);



    // OTHER
    void loadAtlasTexture(const char* path);
    void draw(sf::RenderTarget& target, const Player& player, const Camera& camera) const;

private:
    sf::Texture m_blockAtlas;
    std::unordered_map<int, Chunk> m_activeChunks;
};
