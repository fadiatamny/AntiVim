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
    renderer.init(800, 600, title);
    if (filename.length()) {
        renderer.loadFile(filename);
    }
    renderer.run();
    return 0;
}
