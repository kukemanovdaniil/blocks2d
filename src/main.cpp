#include <iostream>
#include "src/core/engine/Engine.hpp"

int main() {
    Engine engine;
    
    if (!engine.init()) {
        std::cerr << "ENGINE: fatal error, engine not init" << std::endl;
        return -1;
    }

    engine.run();

    return 0;
}
