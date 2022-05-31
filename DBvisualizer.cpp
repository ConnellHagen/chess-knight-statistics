#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Tile.hpp"
#include "utils.hpp"

#include "DBvisualizer.hpp"

DBvisualizer::DBvisualizer(RenderWindow* p_window)
{
    window = p_window;

    light_square = window->load_texture("img/light-square.png");
    dark_square = window->load_texture("img/dark-square.png");

    background_t = window->load_texture("img/background.png");
    background_inf = {0, 0, 1920, 1080};

    background = Background(Vector2f(1, 1), background_t, background_inf);
}

DBvisualizer::~DBvisualizer()
{}

void DBvisualizer::render()
{
    window->render(background);
}