#include <iostream>
#include "lib/Renderer/Renderer.hpp"
#include <thread>
#include <chrono>

const char *title = "AntiVim";

int main(int argc, char *argv[])
{
    Renderer renderer;
    renderer.init(800, 600, title);

    std::thread thread1([&renderer]()
                        { renderer.run(); });

    std::thread thread2([&renderer]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        renderer.renderText("Test Text", { 10, 10 });
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        renderer.renderText("Test Text 2", { 10, 10 }, 0xFF000066, 5.f);
    });

    
    thread1.join();
    thread2.join();

    return 0;
}
