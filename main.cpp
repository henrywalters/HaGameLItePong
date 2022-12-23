#include <memory>
#include <iostream>
#include "hagame/graphics/window.h"

using namespace hg;
using namespace hg::graphics;
using namespace hg::math;

#ifdef __EMSCRIPTEN__
const std::string ASSET_DIR = "./assets/";
#else
const std::string ASSET_DIR = "../assets/";
#endif

std::shared_ptr<Window> window;

void tick() {
    window->render();
}

int main() {
    window = std::make_shared<Window>("HaGameLite");
    window->initialize();
#ifdef __EMSCRIPTEN__
    std::cout << "Hey Wasm!" << "\n";
    emscripten_set_main_loop(tick, 0, false);
#else

    while (window->getRunning()) {
        tick();
    }

    window->close();
#endif

    return 0;
}
