#include "Renderer.hpp"
#include <iostream>

void Renderer::init(int windowWidth, int windowHeight, const char *title)
{
    SDLHelpers::SDLCheckCode(SDL_Init(SDL_INIT_VIDEO));
    SDLHelpers::SDLCheckPtr(this->window = SDL_CreateWindow(
                                title,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                windowWidth,
                                windowHeight,
                                SDL_WINDOW_SHOWN));
    SDLHelpers::SDLCheckPtr(this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED));
    this->fontManager.loadTexture(this->renderer);
    this->running = true;
}

void Renderer::run()
{
    while (this->running)
    {
        const Uint32 start = SDL_GetTicks();

        this->pollEvents();
        Uint32 color = 0xffffffff;

        const float cameraAcceleration = 2.0f;
        Vec2<float> cursorPos(FontManager::charWidth * this->fontManager.scale * this->buffer.cursor.x, FontManager::charHeight * this->fontManager.scale * this->buffer.cursor.y);
        Vec2<float> camVel = (cursorPos - this->cameraPos) * cameraAcceleration;
        this->cameraPos = this->cameraPos + (camVel * DELTA_TIME);

        SDLHelpers::SDLCheckCode(SDL_RenderClear(renderer));
        this->renderBuffer(color, this->fontManager.scale);
        this->renderCursor(color);
        SDLHelpers::SDLCheckCode(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0));
        SDL_RenderPresent(renderer);

        const Uint32 duration = SDL_GetTicks() - start;
        const Uint32 delay = 1000 / FPS;
        if (duration < delay)
        {
            SDL_Delay(delay - duration);
        }
    }
}

Renderer::~Renderer()
{
    this->running = false;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Renderer::renderChar(const char c, Vec2<float> pos, float scale)
{
    size_t index = '?' - FontManager::ASCIILow;
    if (FontManager::ASCIILow <= c && c <= FontManager::ASCIIHigh)
    {
        index = c - FontManager::ASCIILow;
    }
    else if (c == '\r' || c == '\n')
    {
        return;
    }

    SDL_Rect dst = {
        .x = (int)floorf(pos.x),
        .y = (int)floorf(pos.y),
        .w = (int)floorf(FontManager::charWidth * scale),
        .h = (int)floorf(FontManager::charHeight * scale)};

    SDLHelpers::SDLCheckCode(SDL_RenderCopy(this->renderer, this->fontManager.texture, &this->fontManager.glyphs[index], &dst));
}

void Renderer::renderTextChunk(const char *text, size_t len, Vec2<float> pos, Uint32 color, float scale)
{
    this->setTextureColor(color);
    Vec2<float> pen = pos;
    for (size_t i = 0; i < len; i++)
    {
        this->renderChar(text[i], pen, scale);
        pen.x += FontManager::charWidth * scale;
    }
}

void Renderer::setTextureColor(Uint32 color)
{
    SDLHelpers::SDLCheckCode(SDL_SetTextureColorMod(this->fontManager.texture, UNHEX_RGB(color)));
    SDLHelpers::SDLCheckCode(SDL_SetTextureAlphaMod(this->fontManager.texture, UNHEX_A(color)));
}

void Renderer::renderText(const char *text, Vec2<float> pos, Uint32 color, float scale)
{
    this->renderTextChunk(text, strlen(text), pos, color, scale);
}

void Renderer::renderBuffer(Uint32 color, float scale)
{
    size_t row = 0;
    for (auto it = this->buffer.linesBegin(); it != this->buffer.linesEnd(); ++it)
    {
        const Vec2<float> currPos = Vec2<float>(0.f, (float)row++ * FontManager::charHeight * scale);
        const Vec2<float> linePos = SDLHelpers::ProjectPointToCamera(this->window, this->cameraPos, currPos);
        this->renderText((*it).c_str(), linePos, color, scale);
    }
}

void Renderer::renderCursor(Uint32 color)
{
    Vec2<float> pos(FontManager::charWidth * this->fontManager.scale * this->buffer.cursor.x, FontManager::charHeight * this->fontManager.scale * this->buffer.cursor.y);
    Vec2<float> projected = SDLHelpers::ProjectPointToCamera(this->window, this->cameraPos, pos);

    SDL_Rect rect{
        .x = (int)floorf(projected.x),
        .y = (int)floorf(projected.y),
        .w = (int)floorf(FontManager::charWidth * this->fontManager.scale),
        .h = (int)floorf(FontManager::charHeight * this->fontManager.scale)};

    SDLHelpers::SDLCheckCode(SDL_SetRenderDrawColor(this->renderer, UNHEX(color)));
    SDLHelpers::SDLCheckCode(SDL_RenderFillRect(this->renderer, &rect));

    if (this->buffer.currLine() && this->buffer.lineEnd() && this->buffer.cursor.x < this->buffer.lineEnd())
    {
        this->setTextureColor(0xff000000);
        this->renderChar(this->buffer.currLine()[(int)this->buffer.cursor.x], projected, this->fontManager.scale);
    }
}

void Renderer::pollEvents()
{
    SDL_Event event;
    Vec2<int> cursor{0, 0};

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
                this->buffer.erase();
                break;
            case SDLK_DELETE:
                this->buffer.del();
                break;
            case SDLK_RETURN:
                this->buffer.newLine();
                break;
            case SDLK_LEFT:
                this->buffer.move(0, -1);
                break;
            case SDLK_RIGHT:
                this->buffer.move(0, 1);
                break;
            case SDLK_UP:
                cursor.x = this->buffer.cursor.x;
                cursor.y = this->buffer.cursor.y - 1;
                this->buffer.move(cursor);
                break;
            case SDLK_DOWN:
                cursor.x = this->buffer.cursor.x;
                cursor.y = this->buffer.cursor.y + 1;
                this->buffer.move(cursor);
                break;
            case SDLK_HOME:
                cursor.x = this->buffer.lineStart();
                cursor.y = this->buffer.cursor.y;
                this->buffer.move(cursor);
                break;
            case SDLK_END:
                cursor.x = this->buffer.lineEnd();
                cursor.y = this->buffer.cursor.y;
                this->buffer.move(cursor);
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
            this->buffer.insert(event.text.text);
            break;
        }
    }
}