#include "TileData.hpp"

std::array<BlockData, BLOCK_TYPES_COUNT> BlockRegistry;
std::array<WallData, WALL_TYPES_COUNT> WallRegistry;

void initBlockData() {
    BlockRegistry[static_cast<size_t>(BlockType::Air)] = {BlockType::Air, false, true, 0};

    BlockRegistry[static_cast<size_t>(BlockType::Loam)] = {BlockType::Loam, true, true, 0};

    BlockRegistry[static_cast<size_t>(BlockType::Grass)] = {BlockType::Grass, true, true, 1};

    BlockRegistry[static_cast<size_t>(BlockType::Grus)] = {BlockType::Grus, true, true, 2};

    BlockRegistry[static_cast<size_t>(BlockType::Gravel)] = {BlockType::Gravel, true, true, 3};

    BlockRegistry[static_cast<size_t>(BlockType::Limestone)] = {BlockType::Limestone, true, true, 4};

    BlockRegistry[static_cast<size_t>(BlockType::Andesite)] = {BlockType::Andesite, true, true, 5};

    BlockRegistry[static_cast<size_t>(BlockType::Basalt)] = {BlockType::Basalt, true, true, 6};

    BlockRegistry[static_cast<size_t>(BlockType::Oak)] = {BlockType::Oak, true, true, 7};

    BlockRegistry[static_cast<size_t>(BlockType::Leaves)] = {BlockType::Leaves, true, true, 8};
}

void initWallData() {
    WallRegistry[static_cast<size_t>(WallType::None)] = {WallType::None, 0};

    WallRegistry[static_cast<size_t>(WallType::Loam)] = {WallType::Loam, 0};

    WallRegistry[static_cast<size_t>(WallType::Grass)] = {WallType::Grass, 1};

    WallRegistry[static_cast<size_t>(WallType::Grus)] = {WallType::Grus, 2};

    WallRegistry[static_cast<size_t>(WallType::Gravel)] = {WallType::Gravel, 3};

    WallRegistry[static_cast<size_t>(WallType::Limestone)] = {WallType::Limestone, 4};

    WallRegistry[static_cast<size_t>(WallType::Andesite)] = {WallType::Andesite, 5};

    WallRegistry[static_cast<size_t>(WallType::Basalt)] = {WallType::Basalt, 6};

    WallRegistry[static_cast<size_t>(WallType::Oak)] = {WallType::Oak, 7};

    WallRegistry[static_cast<size_t>(WallType::Leaves)] = {WallType::Leaves, 8};
}