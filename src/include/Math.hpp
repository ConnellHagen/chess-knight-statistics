#ifndef math_h
#define math_h

#include <SDL2/SDL.h>
#include <iostream>


struct Vector2f
{
	float x, y;

	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(const float& p_x, const float& p_y)
	:x(p_x), y(p_y)
	{}

	inline void print(){std::cout << x << ", " << y << "\n";}
};

struct Vector2i
{
	int x, y;

	Vector2i()
	:x(0), y(0)
	{}

	Vector2i(const int& p_x, const int& p_y)
	:x(p_x), y(p_y)
	{}

	inline void print(){std::cout << x << ", " << y << "\n";}
};

bool contains_point(const SDL_Rect& rect, const Vector2i& point);

#endif