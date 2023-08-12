#include <iostream>
#include "lib/Renderer/Renderer.hpp"

const char *title = "AntiVim";

int main(int argc, char *argv[])
{
    std::string filename;
    if (argc > 1)
    {
        filename = argv[1];
    }

    Renderer renderer;
    renderer.init(SCREEN_WIDTH, SCREEN_HEIGHT, title);
    if (filename.length()) {
        renderer.loadFile(filename);
    }
    renderer.run();
    return 0;
}
