#include "WorldManager.hpp"

#include "src/game/worldGenerator/default/DefaultGenerator.hpp"
#include "src/core/math/Math.hpp"
#include "src/game/player/Player.hpp"
#include "src/game/worldManager/tileData/TileData.hpp"
#include <filesystem>
#include <print>

void WorldManager::createWorld(int size) {
    DefaultGenerator generator(Math::randomInRange(-999, 999));
    for (int i = -size; i < size; ++i) {
        Chunk chunk;
        chunk.setLocalX(i);
        generator.generate(chunk, chunk.getLocalX()); 
        
        m_activeChunks[i] = std::move(chunk);
    }

    generator.generateTrees(*this, size);

    for (auto& [id, chunk] : m_activeChunks) {
        chunk.updateGeometry();
    }
}

BlockType WorldManager::getGlobalBlock(int blockX, int blockY) {
    if (blockY < 0 || blockY >= static_cast<int>(CHUNK_H)) return BlockType::Air;
    int chunkX = static_cast<int>(std::floor(static_cast<float>(blockX) / CHUNK_W));
    auto it = m_activeChunks.find(chunkX);
    if (it == m_activeChunks.end()) return BlockType::Air;

    int localX = blockX % static_cast<int>(CHUNK_W);
    if (localX < 0) localX += CHUNK_W;
    return it->second.getLocalBlock(static_cast<unsigned int>(localX), static_cast<unsigned int>(blockY));
}

bool WorldManager::setGlobalBlock(int blockX, int blockY, BlockType type) {
    if (blockY < 0 || blockY >= static_cast<int>(CHUNK_H)) return false;
    int chunkX = static_cast<int>(std::floor(static_cast<float>(blockX) / CHUNK_W));
    auto it = m_activeChunks.find(chunkX);
    if (it == m_activeChunks.end()) return false;

    int localX = blockX % static_cast<int>(CHUNK_W);
    if (localX < 0) localX += CHUNK_W;
    it->second.setLocalBlock(static_cast<unsigned int>(localX), static_cast<unsigned int>(blockY), type);
    it->second.updateGeometry();
    return true;
}

WallType WorldManager::getGlobalWall(int blockX, int blockY) {
    if (blockY < 0 || blockY >= static_cast<int>(CHUNK_H)) return WallType::None;
    int chunkX = static_cast<int>(std::floor(static_cast<float>(blockX) / CHUNK_W));
    auto it = m_activeChunks.find(chunkX);
    if (it == m_activeChunks.end()) return WallType::None;

    int localX = blockX % static_cast<int>(CHUNK_W);
    if (localX < 0) localX += CHUNK_W;
    return it->second.getLocalWall(static_cast<unsigned int>(localX), static_cast<unsigned int>(blockY));
}

bool WorldManager::setGlobalWall(int blockX, int blockY, WallType type) {
    if (blockY < 0 || blockY >= static_cast<int>(CHUNK_H)) return false;
    int chunkX = static_cast<int>(std::floor(static_cast<float>(blockX) / CHUNK_W));
    auto it = m_activeChunks.find(chunkX);
    if (it == m_activeChunks.end()) return false;

    int localX = blockX % static_cast<int>(CHUNK_W);
    if (localX < 0) localX += CHUNK_W;
    it->second.setLocalWall(static_cast<unsigned int>(localX), static_cast<unsigned int>(blockY), type);
    it->second.updateGeometry();
    return true;
}



Chunk* WorldManager::getChunkByCoordinate(int chunkX) {
    auto it = m_activeChunks.find(chunkX);
    if (it != m_activeChunks.end()) {
        return &(it->second);
    }
    return nullptr;
}




bool WorldManager::isSolidBlockAt(float globalX, float globalY) {
    if (globalY < 0.0f || globalY >= CHUNK_H_PIXELS) return false;
    
    int chunkX = static_cast<int>(std::floor(globalX / CHUNK_W_PIXELS));
    auto it = m_activeChunks.find(chunkX);
    if (it == m_activeChunks.end()) return false;

    Chunk& chunk = it->second;
        
    float localPixelX = globalX - chunk.getGlobalX();
    unsigned int tileX = static_cast<unsigned int>(localPixelX / TILE_SIZE);
    
    unsigned int tileY = static_cast<unsigned int>(globalY / TILE_SIZE);

    if (tileY >= CHUNK_H) tileY = CHUNK_H - 1;
    if (tileX >= CHUNK_W) tileX = CHUNK_W - 1;

    BlockType block = chunk.getLocalBlock(tileX, tileY);
    if (block == BlockType::Air) return false;

    return BlockRegistry[static_cast<size_t>(block)].m_is_solid;
}







void WorldManager::draw(sf::RenderTarget& target, const Player& player, const Camera& camera) const {
    float halfWidth = (camera.getBaseSize().x * camera.getCurrentZoom()) / 2.0f;
    float cameraLeft = player.getPosition().x - halfWidth;
    float cameraRight = player.getPosition().x + halfWidth;

    int startChunkX = static_cast<int>(std::floor(cameraLeft / CHUNK_W_PIXELS));
    int endChunkX = static_cast<int>(std::floor(cameraRight / CHUNK_W_PIXELS));

    startChunkX -= 1; 
    endChunkX += 1;

    if (!m_blockAtlas) return; 

    for (int x = startChunkX; x <= endChunkX; ++x) {
        auto it = m_activeChunks.find(x);
        if (it != m_activeChunks.end()) {
            it->second.draw(target, *m_blockAtlas); 
        }
    }
}