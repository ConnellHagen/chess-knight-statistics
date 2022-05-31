#ifndef dbvisualizer_h
#define dbvisualizer_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "GUI.hpp"

class DBvisualizer
{
public:
    DBvisualizer(RenderWindow* window);
    ~DBvisualizer();

    void render();

private:
    RenderWindow* window;

    SDL_Texture* light_square;
    SDL_Texture* dark_square;

    SDL_Texture* background_t;
    SDL_Rect background_inf;
    Background background;

    GUI gui;
};

#endif