#pragma once
#include <cstdint>

enum class BlockType : uint8_t {
    Air, 
    Loam, 
    Grass, 
    Grus,
    Gravel,
    Limestone,
    Andesite,
    Basalt,
    Oak,
    Leaves
};

enum class WallType : uint8_t {
    None, 
    Loam, 
    Grass, 
    Grus,
    Gravel,
    Limestone,
    Andesite,
    Basalt,
    Oak,
    Leaves
};