#pragma once
#include "src/worldManager/WorldManager.hpp"
#include "src/worldManager/tileType/TileType.hpp"
#include <cstdlib>

void generateTree(WorldManager& world, int globalBlockX, unsigned int surfaceY) {
    unsigned int treeHeight = 4 + (std::rand() % 10);

    for (unsigned int i = 1; i <= treeHeight; ++i) {
        int wallY = static_cast<int>(surfaceY) - i;
        if (wallY >= 0) {
            world.setGlobalWall(globalBlockX, wallY, WallType::Oak);
        }
    }

    int topY = static_cast<int>(surfaceY) - treeHeight;
    for (int leafY = topY - 4; leafY <= topY; ++leafY) {
        for (int leafX = globalBlockX - 2; leafX <= globalBlockX + 2; ++leafX) {
            if (leafY >= 0) {
                if (leafX == globalBlockX && leafY > topY - 1) {
                    continue;
                }
                world.setGlobalWall(leafX, leafY, WallType::Leaves);
            }
        }
    }
}
