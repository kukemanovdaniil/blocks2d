#pragma once

#include "src/game/worldManager/WorldManager.hpp"
#include "src/game/worldManager/tileType/TileType.hpp"
#include <cstdlib>


void generateTree(WorldManager& world, int globalBlockX, unsigned int surfaceY) {
    unsigned int treeHeight = 4 + (std::rand() % 10);

    for (unsigned int i = 1; i <= treeHeight; ++i) {
        unsigned int wallY = surfaceY + i;
        if (wallY < CHUNK_H) {
            world.setGlobalWall(globalBlockX, wallY, WallType::Oak);
        }
    }

    int topY = static_cast<int>(surfaceY) + treeHeight;
    for (int leafY = topY; leafY <= topY + 4; ++leafY) {
        for (int leafX = globalBlockX - 2; leafX <= globalBlockX + 2; ++leafX) {
            if (leafY < static_cast<int>(CHUNK_H)) {
                world.setGlobalWall(leafX, leafY, WallType::Leaves);
            }
        }
    }
}