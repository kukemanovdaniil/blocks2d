#pragma once

#include "src/game/worldManager/WorldManager.hpp"
#include "src/game/worldManager/tileType/TileType.hpp"
#include <cstdlib>

void generateTree(WorldManager& world, int globalBlockX, unsigned int surfaceY) {
    unsigned int treeHeight = 4 + (std::rand() % 10);

    for (unsigned int i = 1; i <= treeHeight; ++i) {
        if (surfaceY >= i) {
            unsigned int wallY = surfaceY - i;
            world.setGlobalWall(globalBlockX, wallY, WallType::Oak);
        }
    }

    int topY = static_cast<int>(surfaceY) - static_cast<int>(treeHeight);
    
    for (int leafY = topY; leafY >= topY - 4; --leafY) {
        for (int leafX = globalBlockX - 2; leafX <= globalBlockX + 2; ++leafX) {
            if (leafY >= 0) {
                world.setGlobalWall(leafX, leafY, WallType::Leaves);
            }
        }
    }
}
