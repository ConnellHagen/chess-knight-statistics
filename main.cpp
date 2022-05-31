#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>

#include "utils.hpp"
#include "Math.hpp"
#include "RenderWindow.hpp"
#include "DBvisualizer.hpp"

int utils::display::ORIG_DISPLAY_X;
int utils::display::ORIG_DISPLAY_Y;
int utils::display::DISPLAY_WIDTH;
int utils::display::DISPLAY_HEIGHT;
int utils::display::DISPLAY_X;
int utils::display::DISPLAY_Y;

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

    RenderWindow window("Pong", utils::display::DISPLAY_WIDTH, utils::display::DISPLAY_HEIGHT);

    DBvisualizer display(&window);


    // SDL_Window *window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, utils::ORIG_DISPLAY_WIDTH, utils::ORIG_DISPLAY_HEIGHT, 0);
    // if(!window)
    //     std::cout << "Error: Failed to open window\nSDL Error: '%s'\n" << SDL_GetError() << "\n";

    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // if(!renderer)
    //     std::cout << "Error: Failed to create renderer\nSDL Error: '%s'\n" << SDL_GetError() << "\n";

    bool running = true;

    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        // SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        // SDL_RenderClear(renderer);
   

        // SDL_RenderPresent(renderer);
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