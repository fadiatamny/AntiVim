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
    SDLCheckPtr(this->fontSurface = FontManager::loadSurface());
    SDLCheckPtr(this->fontTexture = SDL_CreateTextureFromSurface(this->renderer, this->fontSurface));
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
            std::cout << "Rendering" << this->executionQueue.hasActions() << std::endl;
            this->executionQueue.execute();
            SDLCheckCode(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0));

            SDL_RenderPresent(renderer);
        }
    }
}

void Renderer::dispose()
{
    SDL_DestroyTexture(this->fontTexture);
    SDL_FreeSurface(this->fontSurface);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Renderer::renderChar(const char c, Vec2f pos, Uint32 color, float scale)
{
    this->executionQueue.push([this, c, pos, color, scale]()
                              {
    const size_t index = c - 32;
    const size_t col = index % FontManager::cols;
    const size_t row = index / FontManager::cols;

    SDL_Rect srcRect = {
        .x = (int)col * FontManager::charWidth,
        .y = (int)row * FontManager::charHeight,
        .w = FontManager::charWidth,
        .h = FontManager::charHeight};

    SDL_Rect dstRect = {
        .x = (int)floorf(pos.x),
        .y = (int)floorf(pos.y),
        .w = (int)floorf(FontManager::charWidth * scale),
        .h = (int)floorf(FontManager::charHeight * scale)};

    SDLCheckCode(SDL_SetTextureColorMod(this->fontTexture, color >> 16, color >> 8, color >> 0));
    SDLCheckCode(SDL_SetTextureAlphaMod(this->fontTexture, color >> 24));
    SDLCheckCode(SDL_RenderCopy(this->renderer, this->fontTexture, &srcRect, &dstRect)); });
}

void Renderer::renderText(const char *text, Vec2f pos, Uint32 color, float scale)
{
    Vec2f pen = pos;
    for (size_t i = 0; i < strlen(text); i++)
    {
        this->renderChar(text[i], pen, color, scale);
        pen.x += FontManager::charWidth * scale;
    }
}