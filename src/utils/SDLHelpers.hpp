#ifndef SDLHELPERS_HPP
#define SDLHELPERS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include "./Vec2.hpp"

namespace SDLHelpers
{

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

    /**
     * todo: Why do i need to keep these functions inline for the linker to work !??!?!?! reeeeee
    */
    inline Vec2<float> GetWindowSize(SDL_Window *window)
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        Vec2<float> windowSize((float)w, (float)h);
        return windowSize;
    }

    inline Vec2<float> ProjectPointToCamera(SDL_Window *window, const Vec2<float> &camera, const Vec2<float> &point)
    {
        Vec2<float> pointPos = point - camera;
        Vec2<float> windowSize = GetWindowSize(window);
        Vec2<float> halfWindowSize = windowSize * 0.5f;

        return pointPos + halfWindowSize;
    }

}
#endif // SDLHELPERS_HPP