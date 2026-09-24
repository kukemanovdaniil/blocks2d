#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "src/worldManager/tileType/TileType.hpp"

constexpr unsigned int CHUNK_W = 32;
constexpr unsigned int CHUNK_H = 512;
constexpr unsigned int CHUNK_SIZE = CHUNK_W * CHUNK_H;

constexpr unsigned int TILE_SIZE = 32;

constexpr unsigned int CHUNK_W_PIXELS = CHUNK_W * TILE_SIZE;
constexpr unsigned int CHUNK_H_PIXELS = CHUNK_H * TILE_SIZE;

class Chunk {
public:
    void updateGeometry();

    // GETTERS

    [[nodiscard]] int getLocalX() noexcept { return m_x; }
    [[nodiscard]] float getGlobalX() const noexcept;
    [[nodiscard]] WallType getLocalWall(unsigned int x, unsigned int y) noexcept;
    [[nodiscard]] BlockType getLocalBlock(unsigned int x, unsigned int y) noexcept;
    
    // SETTERS

    void setLocalBlock(unsigned int x, unsigned int y, BlockType type) noexcept;
    void setLocalX(int x) noexcept { m_x = x; }
    void setLocalWall(unsigned int x, unsigned int y, WallType type) noexcept;

    // OTHER

    void draw(sf::RenderTarget& target, const sf::Texture& atlas) const { target.draw(m_mesh, &atlas); }
    
private:
    int m_x{0};

    BlockType blocks[CHUNK_SIZE] = {BlockType::Air};
    WallType walls[CHUNK_SIZE] = {WallType::None};

    sf::VertexArray m_mesh;
};