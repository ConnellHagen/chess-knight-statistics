#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "utils.hpp"
#include "Tile.hpp"
#include "GUI.hpp"
#include "Divider.hpp"

#include "DBvisualizer.hpp"


DBvisualizer::DBvisualizer(RenderWindow* p_window)
    :window(p_window), board_display(SDL_Rect{0, 0, 1080, 1080}), buttons({1080, 0, 840, 1080})
{
    light_square = window->load_texture("img/light-square.png");
    dark_square = window->load_texture("img/dark-square.png");

    background_t = window->load_texture("img/background.png");
    background_inf = {0, 0, 1920, 1080};

    color_switch_black = window->load_texture("img/buttons/color-switch-black.png");
    color_switch_white = window->load_texture("img/buttons/color-switch-white.png");
    color_switch_hover = window->load_texture("img/buttons/color-switch-hover.png");
    color_switch_pressed = window->load_texture("img/buttons/color-switch-pressed.png");

    background = Background(Vector2f(1, 1), background_t, background_inf);

    // board_display.add_chess_tile();

    GUI buttons_gui;
    ToggleButton color_switcher(Vector2f(50, 50), color_switch_white, color_switch_black, color_switch_hover, color_switch_pressed, SDL_Rect{0, 0, 32, 32}, TOGGLE_COLOR_SWITCHER, MIDDLE_CENTER);
    buttons_gui.add(color_switcher);
    buttons.add_gui(buttons_gui);
}

DBvisualizer::~DBvisualizer()
{
    SDL_DestroyTexture(light_square);
    SDL_DestroyTexture(dark_square);
    SDL_DestroyTexture(background_t);
    SDL_DestroyTexture(color_switch_black);
    SDL_DestroyTexture(color_switch_white);
    SDL_DestroyTexture(color_switch_hover);
    SDL_DestroyTexture(color_switch_pressed);
}

std::vector<BUTTON_FUNCTION> DBvisualizer::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
    std::vector<BUTTON_FUNCTION> functions;
    for(BUTTON_FUNCTION func : board_display.update(key_pushes, mouse_coords, delta_time))
    {
        functions.push_back(func);
    }

    for(BUTTON_FUNCTION func : buttons.update(key_pushes, mouse_coords, delta_time))
    {
        functions.push_back(func);
    }

    return functions;
}


void DBvisualizer::render()
{
    window->render(background);
    window->render(board_display);
    window->render(buttons);
}