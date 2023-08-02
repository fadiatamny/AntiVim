#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../FontManager/FontManager.hpp"
#include "../../utils/Vec2f.hpp"
#include "../../utils/ExecutionQueue.hpp"

class Renderer
{
public:
    Renderer() {}
    ~Renderer() {}

    void init(int windowWidth, int windowHeight, const char *title = "Window");
    void run();
    void dispose();

    
    void renderChar(const char c, Vec2f pos, Uint32 color = 0xffffff, float scale = 1.f);
    void renderText(const char *text, Vec2f pos, Uint32 color = 0xffffff, float scale = 1.f);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *fontSurface;
    SDL_Texture *fontTexture;
    ExecutionQueue executionQueue;
};

#endif // RENDERER_HPP