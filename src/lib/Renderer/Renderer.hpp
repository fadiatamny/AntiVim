#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../FontManager/FontManager.hpp"
#include "../../utils/Vec2f.hpp"
#include "../../utils/ExecutionQueue.hpp"
#include <string>

class Renderer
{
public:
    Renderer(): fontManager(FontManager()) {}
    ~Renderer();

    void init(int windowWidth, int windowHeight, const char *title = "Window");
    void run();
    
    void renderChar(const char c, Vec2f pos, float scale = 1.f);
    void renderTextChunk(const char *text, size_t len, Vec2f pos, Uint32 color = 0xffffff, float scale = 1.f);
    void renderText(const char *text, Vec2f pos, Uint32 color = 0xffffff, float scale = 1.f);
    void renderBuffer(Vec2f pos, Uint32 color = 0xffffff, float scale = 1.f);
    void renderCursor(Uint32 color = 0xffffff);

protected:
    void pollEvents();
    void handleTextEvent(SDL_TextInputEvent &event);
    void setTextureColor(Uint32 color);

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    FontManager fontManager;
    ExecutionQueue executionQueue;
    std::string buffer = "";
    size_t cursor = 0;
};

#endif // RENDERER_HPP