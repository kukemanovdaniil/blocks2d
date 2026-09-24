#include "Chunk.hpp"
#include "src/worldManager/tileData/TileData.hpp"

float Chunk::getGlobalX() const noexcept {
    float globalX{static_cast<float>(m_x * static_cast<int>(CHUNK_W)) * TILE_SIZE};
    return globalX;
}

BlockType Chunk::getLocalBlock(unsigned int x, unsigned int y) noexcept {
    if (x < CHUNK_W && y < CHUNK_H) {
        return blocks[x + (y * CHUNK_W)];
    }
    return BlockType::Air;
}

void Chunk::setLocalBlock(unsigned int x, unsigned int y, BlockType type) noexcept {
    if (x < CHUNK_W && y < CHUNK_H) {
        blocks[x + (y * CHUNK_W)] = type;
    }
}

WallType Chunk::getLocalWall(unsigned int x, unsigned int y) noexcept {
    if (x < CHUNK_W && y < CHUNK_H) {
        return walls[x + (y * CHUNK_W)];
    }
    return WallType::None;
}

void Chunk::setLocalWall(unsigned int x, unsigned int y, WallType type) noexcept {
    if (x < CHUNK_W && y < CHUNK_H) {
        walls[x + (y * CHUNK_W)] = type;
    }
}

void Chunk::updateGeometry() {
    m_mesh.setPrimitiveType(sf::PrimitiveType::Triangles);

    unsigned int totalTilesToRender = 0;

    for (unsigned int index = 0; index < CHUNK_SIZE; ++index) {
        BlockType currentBlockType = blocks[index];
        WallType currentWallType = walls[index];

        if (currentWallType != WallType::None) {
            if (currentBlockType == BlockType::Air) {
                totalTilesToRender += 1;
            } else {
                const BlockData& blockData = BlockRegistry[static_cast<size_t>(currentBlockType)];
                if (!blockData.m_hides_behind) {
                    totalTilesToRender += 1;
                }
            }
        }

        if (currentBlockType != BlockType::Air) {
            totalTilesToRender += 1;
        }
    }

    m_mesh.resize(totalTilesToRender * 6);
    
    unsigned int vertexCount = 0;
    constexpr int TEX_SIZE = 16;

    auto addTileToMesh = [&](unsigned int x, unsigned int y, unsigned int texIndex, sf::Color color) {
        float posX0 = getGlobalX() + x * TILE_SIZE;
        float posX1 = posX0 + TILE_SIZE;
        
        float flippedY = static_cast<float>(CHUNK_H - 1 - y); 
        float posY0 = flippedY * TILE_SIZE;
        float posY1 = posY0 + TILE_SIZE;

        float texX0 = static_cast<float>(texIndex * TEX_SIZE);
        float texX1 = texX0 + TEX_SIZE;
        float texY0 = 0.0f;
        float texY1 = static_cast<float>(TEX_SIZE);

        m_mesh[vertexCount + 0].position = sf::Vector2f(posX0, posY0);
        m_mesh[vertexCount + 0].texCoords = sf::Vector2f(texX0, texY0);
        m_mesh[vertexCount + 0].color = color;

        m_mesh[vertexCount + 1].position = sf::Vector2f(posX0, posY1);
        m_mesh[vertexCount + 1].texCoords = sf::Vector2f(texX0, texY1);
        m_mesh[vertexCount + 1].color = color;

        m_mesh[vertexCount + 2].position = sf::Vector2f(posX1, posY0);
        m_mesh[vertexCount + 2].texCoords = sf::Vector2f(texX1, texY0);
        m_mesh[vertexCount + 2].color = color;

        m_mesh[vertexCount + 3].position = sf::Vector2f(posX0, posY1);
        m_mesh[vertexCount + 3].texCoords = sf::Vector2f(texX0, texY1);
        m_mesh[vertexCount + 3].color = color;

        m_mesh[vertexCount + 4].position = sf::Vector2f(posX1, posY1);
        m_mesh[vertexCount + 4].texCoords = sf::Vector2f(texX1, texY1);
        m_mesh[vertexCount + 4].color = color;

        m_mesh[vertexCount + 5].position = sf::Vector2f(posX1, posY0);
        m_mesh[vertexCount + 5].texCoords = sf::Vector2f(texX1, texY0);
        m_mesh[vertexCount + 5].color = color;

        vertexCount += 6;
    };

    for (unsigned int y = 0; y < CHUNK_H; ++y) {
        for (unsigned int x = 0; x < CHUNK_W; ++x) {
            WallType currentWallType = getLocalWall(x, y);

            if (currentWallType != WallType::None) {
                BlockType currentBlockType = getLocalBlock(x, y);
                
                bool shouldRenderWall = false;
                if (currentBlockType == BlockType::Air) {
                    shouldRenderWall = true;
                } else {
                    const BlockData& blockData = BlockRegistry[static_cast<size_t>(currentBlockType)];
                    if (!blockData.m_hides_behind) {
                        shouldRenderWall = true;
                    }
                }

                if (shouldRenderWall) {
                    const auto& wallData = WallRegistry[static_cast<size_t>(currentWallType)];
                    addTileToMesh(x, y, wallData.m_texIndex, sf::Color(175, 175, 175));
                }
            }
        }
    }

    for (unsigned int y = 0; y < CHUNK_H; ++y) {
        for (unsigned int x = 0; x < CHUNK_W; ++x) {
            BlockType currentBlockType = getLocalBlock(x, y);
            
            if (currentBlockType != BlockType::Air) {
                const auto& blockData = BlockRegistry[static_cast<size_t>(currentBlockType)];
                addTileToMesh(x, y, blockData.m_texIndex, sf::Color::White);
            }
        }
    }
}
