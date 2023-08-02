#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP
#include "../../utils/SDLHelpers.hpp"

class FontManager
{
public:
    static const unsigned short ASCIILow = 32;
    static const unsigned short ASCIIHigh = 126;

    static const int width = 128;
    static const int height = 64;
    static const int cols = 18;
    static const int rows = 7;
    static const int charWidth = (width / cols);
    static const int charHeight = (height / rows);

private:
    static inline const char *filePath = "assets/font.png";

public:
    ~FontManager();
    void loadTexture(SDL_Renderer *renderer);

public:
    SDL_Rect glyphs[ASCIIHigh - ASCIILow + 1] = {0};
    SDL_Texture *texture = nullptr;
};

#endif // FONTMANAGER_HPP