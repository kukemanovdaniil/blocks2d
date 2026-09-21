#include "DefaultGenerator.hpp"
#include "src/worldManager/tileType/TileType.hpp" 
#include "src/worldGenerator/default/structure/tree/TreeGenerator.hpp"
#include <cmath>
#include <print>

DefaultGenerator::DefaultGenerator(int seed) {
    m_landscapeNoise.SetSeed(seed);
    m_landscapeNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    m_landscapeNoise.SetFrequency(0.005f);

    m_cavesNoise.SetSeed(seed + 1); 
    m_cavesNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    m_cavesNoise.SetFrequency(0.019f);

    std::srand(static_cast<unsigned int>(seed));
}

void DefaultGenerator::generate(Chunk& chunk, int chunkX) {
    generateLandscape(chunk, chunkX);
    generateVegetation(chunk, chunkX);
    generateCaves(chunk, chunkX);

    chunk.updateGeometry();
}

void DefaultGenerator::generateLandscape(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        const int globalX = chunkX * static_cast<int>(CHUNK_W) + static_cast<int>(x);
        const unsigned int surfaceY = calculateSurfaceY(globalX);
        
        for (unsigned int y = 0; y <= surfaceY; ++y) {
            if (y <= 3) {
                chunk.setLocalBlock(x, y, BlockType::Basalt);
                chunk.setLocalWall(x, y, WallType::Basalt);
            }
            else if (y < surfaceY / 3) {
                chunk.setLocalBlock(x, y, BlockType::Andesite);
                chunk.setLocalWall(x, y, WallType::Andesite);
            }
            else if (y < (surfaceY - 9)) {
                chunk.setLocalBlock(x, y, BlockType::Limestone);    
                chunk.setLocalWall(x, y, WallType::Limestone);  
            }
            else if (y < (surfaceY - 7)) {
                chunk.setLocalBlock(x, y, BlockType::Gravel);
                chunk.setLocalWall(x, y, WallType::Gravel);
            }
            else {
                chunk.setLocalBlock(x, y, BlockType::Grus);
                chunk.setLocalWall(x, y, WallType::Grus);
            }
        }
    }
}

void DefaultGenerator::generateVegetation(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        int globalX = chunkX * CHUNK_W + x;
        unsigned int surfaceY = calculateSurfaceY(globalX);
        
        for (unsigned int y = 0; y <= surfaceY; ++y) {
            if (y == surfaceY) {
                chunk.setLocalBlock(x, y, BlockType::Grass);
                chunk.setLocalWall(x, y, WallType::Grass);
            }
            else if (y < surfaceY && y > (surfaceY - 5)) {
                chunk.setLocalBlock(x, y, BlockType::Loam);
                chunk.setLocalWall(x, y, WallType::Loam);
            }
        }
    }
}

void DefaultGenerator::generateCaves(Chunk& chunk, int chunkX) {     
    for (unsigned int x = 0; x < CHUNK_W; ++x) {         
        const int globalX = chunkX * static_cast<int>(CHUNK_W) + static_cast<int>(x);         
        const int surfaceY = static_cast<int>(calculateSurfaceY(globalX));          

        for (int y = 4; y < surfaceY + 1; ++y) {             
            const float caveNoiseValue = calculateCaveValue(globalX, y);             

            if (std::abs(caveNoiseValue) < 0.08f) {                 
                chunk.setLocalBlock(x, static_cast<unsigned int>(y), BlockType::Air);             
            }         
        }     
    } 
}






void DefaultGenerator::generateTrees(WorldManager& world, int size) {
    for (int i = -size; i < size; ++i) {
        for (unsigned int x = 0; x < CHUNK_W; ++x) {
            int globalBlockX = (i * static_cast<int>(CHUNK_W)) + static_cast<int>(x);
            unsigned int surfaceY = calculateSurfaceY(globalBlockX);

            if (std::rand() % 100 > 15) continue; 
            if (world.getGlobalBlock(globalBlockX, static_cast<int>(surfaceY)) != BlockType::Grass) continue;

            generateTree(world, globalBlockX, surfaceY);
        }
    }
}
