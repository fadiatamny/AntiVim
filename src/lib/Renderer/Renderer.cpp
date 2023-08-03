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
    this->running = true;
}

void Renderer::run()
{
    while (this->running)
    {
        this->pollEvents();

        // if (this->executionQueue.hasActions())
        // {
        //     SDLCheckCode(SDL_RenderClear(renderer));
        //     this->executionQueue.execute();
        //     SDLCheckCode(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0));

        //     SDL_RenderPresent(renderer);
        // }

        Uint32 color = 0xffffffff;
        SDLCheckCode(SDL_RenderClear(renderer));
        this->renderBuffer({0, 0}, color, this->fontManager.scale);
        this->renderCursor(color);
        SDLCheckCode(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0));
        SDL_RenderPresent(renderer);
    }
}

Renderer::~Renderer()
{
    this->running = false;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Renderer::renderChar(const char c, Vec2f pos, float scale)
{
    // this->executionQueue.push([this, c, pos, scale]()
    //                           {
    const size_t index = c - 32;

    SDL_Rect dst = {
        .x = (int)floorf(pos.x),
        .y = (int)floorf(pos.y),
        .w = (int)floorf(FontManager::charWidth * scale),
        .h = (int)floorf(FontManager::charHeight * scale)};

    SDLCheckCode(SDL_RenderCopy(this->renderer, this->fontManager.texture, &this->fontManager.glyphs[index], &dst));
    //  });
}

void Renderer::renderTextChunk(const char *text, size_t len, Vec2f pos, Uint32 color, float scale)
{
    this->setTextureColor(color);
    Vec2f pen = pos;
    for (size_t i = 0; i < len; i++)
    {
        this->renderChar(text[i], pen, scale);
        pen.x += FontManager::charWidth * scale;
    }
}

void Renderer::setTextureColor(Uint32 color)
{
    // SDLCheckCode(SDL_SetTextureColorMod(this->fontManager.texture, (color >> 0) & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff));
    // SDLCheckCode(SDL_SetTextureAlphaMod(this->fontManager.texture, (color >> 24) & 0xff));
    SDLCheckCode(SDL_SetTextureColorMod(this->fontManager.texture, UNHEX_RGB(color)));
    SDLCheckCode(SDL_SetTextureAlphaMod(this->fontManager.texture, UNHEX_A(color)));
}

void Renderer::renderText(const char *text, Vec2f pos, Uint32 color, float scale)
{
    this->renderTextChunk(text, strlen(text), pos, color, scale);
}

void Renderer::renderBuffer(Vec2f pos, Uint32 color, float scale)
{
    this->renderText(this->buffer.c_str(), pos, color, scale);
}

void Renderer::renderCursor(Uint32 color)
{
    Vec2f cursorPos(FontManager::charWidth * this->fontManager.scale * this->cursor, 0.f);
    SDL_Rect rect{
        .x = (int)floorf(cursorPos.x),
        .y = (int)floorf(cursorPos.y),
        .w = FontManager::charWidth * this->fontManager.scale,
        .h = FontManager::charHeight * this->fontManager.scale};

    SDLCheckCode(SDL_SetRenderDrawColor(this->renderer, UNHEX(color)));
    SDLCheckCode(SDL_RenderFillRect(this->renderer, &rect));

    if (this->cursor < this->buffer.length())
    {
        this->setTextureColor(0xff000000);
        this->renderChar(this->buffer[this->cursor], cursorPos, this->fontManager.scale);
    }
}

void Renderer::pollEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            this->running = false;
            break;

        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
#pragma region cursor stuff
            case SDLK_BACKSPACE:
                if (this->buffer.length() > 0)
                {
                    this->buffer.pop_back();
                    --this->cursor;
                }
                break;
            case SDLK_RETURN:
                if (this->buffer.length() > 0)
                {
                    this->buffer += '\n';
                }
                break;
            case SDLK_LEFT:
                if (this->cursor > 0)
                {
                    --this->cursor;
                }
                break;
            case SDLK_RIGHT:
                if (this->cursor < this->buffer.length())
                {
                    ++this->cursor;
                }
                break;
            case SDLK_HOME:
                this->cursor = 0;
                break;
            case SDLK_END:
                this->cursor = this->buffer.length();
                break;

#pragma endregion

                // #pragma region size stuff
                //             case SDLK_EQUALS:
                //             case SDLK_PLUS:
                //                 if (event.key.keysym.mod & KMOD_CTRL)
                //                 {
                //                     this->fontManager.scale += 0.1f;
                //                 }
                //                 break;
                //             case SDLK_MINUS:
                //             case SDLK_UNDERSCORE:
                //                 if (event.key.keysym.mod & KMOD_CTRL)
                //                 {
                //                     this->fontManager.scale -= 0.1f;
                //                 }
                //                 break;
                // #pragma endregion
            }
        }
        break;

        case SDL_TEXTINPUT:
        {
            this->buffer += event.text.text;
            this->cursor = this->buffer.length();
        }
        break;
        }
    }
}