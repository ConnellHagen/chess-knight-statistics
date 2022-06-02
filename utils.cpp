#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

#include "Math.hpp"

#include "utils.hpp"


float utils::hire_time_in_seconds()
{
    float t = SDL_GetTicks();
    t *= 0.001f;

    return t;
}

int utils::random(const int& lower, const int& upper)
{
    srand((unsigned int) time (NULL));
    return rand() % (upper - lower + 1) + lower;
}

void utils::print_rect(const SDL_Rect& rect)
{
    std::cout << "x: " << rect.x << ", y: " << rect.y << ", w: " << rect.w << ", h: " << rect.h << "\n";
}

Vector2i utils::shift_coords(const Vector2i& coords)
{
    int new_x = coords.x / utils::get_scale().x;
    int new_y = coords.y / utils::get_scale().y;

    Vector2i new_coords = Vector2i(new_x, new_y);

    return new_coords;
}

Vector2f utils::get_scale()
{
    return Vector2f(display::DISPLAY_WIDTH / static_cast<float>(ORIG_DISPLAY_WIDTH), display::DISPLAY_HEIGHT / static_cast<float>(ORIG_DISPLAY_HEIGHT));
}
	
