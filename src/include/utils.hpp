#ifndef utils_h
#define utils_h

#include <SDL2/SDL.h>
#include <ctime>
#include <cmath>
#include <vector>

#include "Math.hpp"

namespace utils
{
	float hire_time_in_seconds();

	int random(const int& lower, const int& upper);

	Vector2i shift_coords(const Vector2i& coords);

	Vector2f get_scale();

	constexpr int ORIG_DISPLAY_WIDTH{1920};
	constexpr int ORIG_DISPLAY_HEIGHT{1080};
	class display
	{
	public:
		static int ORIG_DISPLAY_X;
		static int ORIG_DISPLAY_Y;

		static int DISPLAY_WIDTH;
		static int DISPLAY_HEIGHT;
		static int DISPLAY_X;
		static int DISPLAY_Y;
	};

}

enum RENDER_MODE
{
	TOP_LEFT, TOP_CENTER, TOP_RIGHT, MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT, BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
};

#endif