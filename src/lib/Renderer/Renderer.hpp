#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../FontManager/FontManager.hpp"
#include "../../utils/Vec2.hpp"
#include "../Buffer/Buffer.hpp"
#include <string>

class Renderer
{
public:
    Renderer(): fontManager(FontManager()), buffer(Buffer()) {}
    ~Renderer();

    void init(int windowWidth, int windowHeight, const char *title = "Window");
    void run();
    
    void renderChar(const char c, Vec2<float> pos, float scale = 1.f);
    void renderTextChunk(const char *text, size_t len, Vec2<float> pos, Uint32 color = 0xffffff, float scale = 1.f);
    void renderText(const char *text, Vec2<float> pos, Uint32 color = 0xffffff, float scale = 1.f);
    void renderBuffer(Uint32 color = 0xffffff, float scale = 1.f);
    void renderCursor(Uint32 color = 0xffffff);

protected:
    void pollEvents();
    void handleTextEvent(SDL_TextInputEvent &event);
    void setTextureColor(Uint32 color);
    void appendText(const char *text);

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    FontManager fontManager;
    Buffer buffer;
};

#endif // RENDERER_HPP