#include <iostream>
#include "lib/Renderer/Renderer.hpp"
#include <thread>
#include <chrono>

const char *title = "AntiVim";

int main(int argc, char *argv[])
{
    Renderer renderer;
    renderer.init(800, 600, title);
    renderer.run();
    return 0;
}
