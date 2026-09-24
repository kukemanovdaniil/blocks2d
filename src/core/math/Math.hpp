#pragma once

#include "src/worldManager/chunk/Chunk.hpp"

namespace Math {
    int randomInRange(const int min, const int max) noexcept;
    inline bool isChunkVisible(const Chunk& chunk, float cameraLeft, float cameraRight) noexcept;
}