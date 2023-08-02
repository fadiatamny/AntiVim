#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP
#include "../../utils/SDLHelpers.hpp"


class FontManager
{
public:
    static SDL_Surface * loadSurface();

public:
    static inline const char* filePath = "assets/font.png";
    static const int width = 128;
    static const int height = 64;
    static const int cols = 18;
    static const int rows = 7;
    static const int charWidth = (width / cols);
    static const int charHeight = (height / rows);
};

#endif // FONTMANAGER_HPP