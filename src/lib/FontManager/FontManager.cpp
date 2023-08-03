#include "FontManager.hpp"

// needed for the bitmap
#define STB_IMAGE_IMPLEMENTATION
#include "../../utils/stb_image.h"

void FontManager::loadTexture(SDL_Renderer *renderer)
{
    int width, height, channels;
    unsigned char *data = stbi_load(FontManager::filePath, &width, &height, &channels, 0);
    if (data == nullptr)
    {
        std::cout << "Error loading image: " << filePath << " - " << stbi_failure_reason() << std::endl;
        exit(1);
    }

    SDL_Surface *surface = (SDL_Surface *)SDLCheckPtr(SDL_CreateRGBSurfaceWithFormatFrom(
        data,
        width,
        height,
        8 * channels,
        width * channels,
        SDL_PIXELFORMAT_RGB24));

    SDLCheckPtr(this->texture = SDL_CreateTextureFromSurface(renderer, surface));
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