#include <SDL2/SDL.h>
#include <iostream>

#include "Math.hpp"


bool contains_point(const SDL_Rect& rect, const Vector2i& point)
{
    return point.x >= rect.x && point.x < rect.x + rect.w && point.y >= rect.y && point.y < rect.y + rect.h;
}