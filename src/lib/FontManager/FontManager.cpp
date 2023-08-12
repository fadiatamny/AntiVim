#include "FontManager.hpp"

// needed for the bitmap
#define STB_IMAGE_IMPLEMENTATION
#include "../../utils/stb_image.h"

void FontManager::loadTexture(SDL_Renderer *renderer)
{
    int width, height, channels;
    unsigned char *data = stbi_load(FontManager::filePath, &width, &height, &channels, STBI_rgb_alpha);
    if (data == nullptr)
    {
        std::cout << "Error loading image: " << filePath << " - " << stbi_failure_reason() << std::endl;
        exit(1);
    }

    const int depth = 32;
    const int pitch = width * 4;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const uint32_t rmask = 0xff000000;
        const uint32_t gmask = 0x00ff0000;
        const uint32_t bmask = 0x0000ff00;
        const uint32_t amask = 0x000000ff;
    #else
        const uint32_t rmask = 0x000000ff;
        const uint32_t gmask = 0x0000ff00;
        const uint32_t bmask = 0x00ff0000;
        const uint32_t amask = 0xff000000;
    #endif

    SDL_Surface *surface = (SDL_Surface *)SDLHelpers::SDLCheckPtr(SDL_CreateRGBSurfaceFrom(
        (void*)data,
        width,
        height,
        depth,
        pitch,
        rmask,
        gmask,
        bmask,
        amask
    ));

    SDLHelpers::SDLCheckCode(SDL_SetColorKey(surface, SDL_TRUE, 0xff000000));

    SDLHelpers::SDLCheckPtr(this->texture = SDL_CreateTextureFromSurface(renderer, surface));
    SDL_FreeSurface(surface);

    for (size_t ascii = ASCIILow; ascii <= ASCIIHigh; ++ascii)
    {
        const size_t index = ascii - 32;
        if ( index >= ASCIIHigh - ASCIILow + 1) {
            std::cout << "index out of bounds: " << index << std::endl;
            exit(1);
        }

        const size_t col = index % FontManager::cols;
        const size_t row = index / FontManager::cols;

        SDL_Rect rect = {
            .x = (int)col * FontManager::charWidth,
            .y = (int)row * FontManager::charHeight,
            .w = FontManager::charWidth,
            .h = FontManager::charHeight};
        this->glyphs[index] = rect;
    }
}

FontManager::~FontManager()
{
    SDL_DestroyTexture(this->texture);
}