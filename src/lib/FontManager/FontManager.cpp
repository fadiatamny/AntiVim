#include "FontManager.hpp"

// needed for the bitmap
#define STB_IMAGE_IMPLEMENTATION
#include "../../utils/stb_image.h"

SDL_Surface * FontManager::loadSurface()
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

    return surface;
}