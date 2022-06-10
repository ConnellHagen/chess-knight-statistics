#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>

#include "Math.hpp"
#include "utils.hpp"
#include "RenderWindow.hpp"
#include "DBvisualizer.hpp"


// static variables
int utils::display::ORIG_DISPLAY_X;
int utils::display::ORIG_DISPLAY_Y;
int utils::display::DISPLAY_WIDTH;
int utils::display::DISPLAY_HEIGHT;
int utils::display::DISPLAY_X;
int utils::display::DISPLAY_Y;

bool Button::mouse_clicked = false;
bool Button::mouse_held = false;

int main(int argc, char* args[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. Error " << SDL_GetError() << "\n";
	
	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << "\n";

	if(TTF_Init() != 0)
		std::cout << "TTF_Init has failed. Error: " << SDL_GetError() << "\n";

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    utils::display::DISPLAY_WIDTH = 1280; //utils::ORIG_DISPLAY_WIDTH;
	utils::display::DISPLAY_HEIGHT = 720; //utils::ORIG_DISPLAY_HEIGHT;
	utils::display::DISPLAY_X = utils::display::ORIG_DISPLAY_X;
	utils::display::DISPLAY_Y = utils::display::ORIG_DISPLAY_Y;

    RenderWindow window("Database Visualizer", utils::display::DISPLAY_WIDTH, utils::display::DISPLAY_HEIGHT);

    DBVisualizer display(&window);

    const float time_step = .016666;
	float accumulator = 0.0f;
	float current_time = utils::hire_time_in_seconds();
	int last_frame_ticks = SDL_GetTicks();

    bool running = true;

    SDL_Event event;

    // 0: left click
    std::vector<bool> key_pushes = std::vector<bool>(2, false);
    Vector2i mouse_coords;

    while(running)
    {
        float new_time = utils::hire_time_in_seconds();
		float loop_time = new_time - current_time;
		current_time = new_time;
		accumulator += loop_time;

		while(accumulator >= time_step)
		{
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {}
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {}
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        key_pushes[0] = true;
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    switch(event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        key_pushes[0] = false;
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    mouse_coords = utils::shift_coords(Vector2i(event.motion.x, event.motion.y));
                    break;
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
                }
            }

            accumulator -= time_step;

			float current_frame_ticks = SDL_GetTicks();
			const float delta_time = (current_frame_ticks - last_frame_ticks) / 1000;

			// updating
			display.update(key_pushes, mouse_coords, delta_time);

			last_frame_ticks = SDL_GetTicks();
        }
        window.clear();

		//rendering
		display.render();
		
		//displaying
		window.display();
    }

    // window.clean_up();
	SDL_Quit();

	return 0;
}