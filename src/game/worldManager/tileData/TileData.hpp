#pragma once

#include "src/game/worldManager/tileType/TileType.hpp"
#include <array>
#include <cstddef>

constexpr size_t BLOCK_TYPES_COUNT = 10; 
constexpr size_t WALL_TYPES_COUNT = 10; 

struct BlockData {
    BlockType m_type;
    bool m_collision;
    bool m_hides_behind;
    unsigned int m_texIndex;
};

struct WallData {
    WallType m_type;
    unsigned int m_texIndex;
};

extern std::array<BlockData, BLOCK_TYPES_COUNT> BlockRegistry;
extern std::array<WallData, WALL_TYPES_COUNT> WallRegistry;

void initBlockData();
void initWallData();