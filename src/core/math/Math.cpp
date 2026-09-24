#include "src/core/math/Math.hpp"

#include <SFML/Graphics.hpp>
#include <random>

int Math::randomInRange(const int min, const int max) noexcept {
    static thread_local std::random_device seed;
    static thread_local std::mt19937 gen(seed());
    std::uniform_int_distribution<int> distance(min, max);

    return distance(gen);
}


inline bool Math::isChunkVisible(const Chunk& chunk, float cameraLeft, float cameraRight) noexcept {
    float chunkLeft = chunk.getGlobalX();
    float chunkRight = chunkLeft + CHUNK_W_PIXELS;

    return chunkRight >= cameraLeft && chunkLeft <= cameraRight;
}
