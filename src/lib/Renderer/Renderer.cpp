#include "Renderer.hpp"
#include <iostream>

void Renderer::init(int windowWidth, int windowHeight, const char *title)
{
    SDLCheckCode(SDL_Init(SDL_INIT_VIDEO));
    SDLCheckPtr(this->window = SDL_CreateWindow(
                    title,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    windowWidth,
                    windowHeight,
                    SDL_WINDOW_SHOWN));
    SDLCheckPtr(this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED));
    this->fontManager.loadTexture(this->renderer);
}

void Renderer::run()
{
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
                break;
            }
        }

        if (this->executionQueue.hasActions())
        {
            SDLCheckCode(SDL_RenderClear(renderer));
            this->executionQueue.execute();
            SDLCheckCode(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0));

            SDL_RenderPresent(renderer);
        }
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Renderer::renderChar(const char c, Vec2f pos, float scale)
{
    this->executionQueue.push([this, c, pos, scale]()
                              {
    const size_t index = c - 32;

    SDL_Rect dst = {
        .x = (int)floorf(pos.x),
        .y = (int)floorf(pos.y),
        .w = (int)floorf(FontManager::charWidth * scale),
        .h = (int)floorf(FontManager::charHeight * scale)};

    SDLCheckCode(SDL_RenderCopy(this->renderer, this->fontManager.texture, &this->fontManager.glyphs[index], &dst)); });
}

void Renderer::renderText(const char *text, Vec2f pos, Uint32 color, float scale)
{
    SDLCheckCode(SDL_SetTextureColorMod(this->fontManager.texture, (color >> 0) & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff));
    SDLCheckCode(SDL_SetTextureAlphaMod(this->fontManager.texture, (color >> 24) & 0xff));

    Vec2f pen = pos;
    for (size_t i = 0; i < strlen(text); i++)
    {
        this->renderChar(text[i], pen, scale);
        pen.x += FontManager::charWidth * scale;
    }
}