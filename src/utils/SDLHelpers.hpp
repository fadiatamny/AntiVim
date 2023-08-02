#ifndef SDLHELPERS_HPP
#define SDLHELPERS_HPP

#include <iostream>
#include <SDL2/SDL.h>

inline void SDLCheckCode(int code)
{
    if (code < 0)
    {
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}
inline void *SDLCheckPtr(void *ptr)
{
    if (ptr == nullptr)
    {
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    return ptr;
}

#endif // SDLHELPERS_HPP