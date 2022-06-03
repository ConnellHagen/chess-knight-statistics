#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils.hpp"
#include "Tile.hpp"
#include "GUI.hpp"
#include "Divider.hpp"
#include "RenderWindow.hpp"

#include "DBvisualizer.hpp"


DBvisualizer::DBvisualizer(RenderWindow* p_window)
    :window(p_window), board_display(SDL_Rect{0, 0, 1080, 1080}), buttons({1080, 0, 840, 1080})
{
    // loading background and textures
    background_t = window->load_texture("img/background.png");
    background_inf = {0, 0, 1920, 1080};

    light_square = window->load_texture("img/light-square.png");
    dark_square = window->load_texture("img/dark-square.png");

    color_switch_black = window->load_texture("img/buttons/color-switch-black.png");
    color_switch_white = window->load_texture("img/buttons/color-switch-white.png");
    color_switch_white_hover = window->load_texture("img/buttons/color-switch-white-hover.png");
    color_switch_black_hover = window->load_texture("img/buttons/color-switch-black-hover.png");
    color_switch_pressed = window->load_texture("img/buttons/color-switch-pressed.png");

    board_flip = window->load_texture("img/buttons/board-flip.png");
    board_flip_hover = window->load_texture("img/buttons/board-flip-hover.png");
    board_flip_pressed = window->load_texture("img/buttons/board-flip-pressed.png");


    background = Background(Vector2f(1, 1), background_t, background_inf);

    GUI buttons_gui;

    ToggleButton color_switcher
    (
        SDL_Rect{80, 80, 200, 200}, SDL_Rect{0, 0, 32, 32},
        TOP_LEFT, SWITCH_COLORS,
        std::vector<SDL_Texture*>{color_switch_white, color_switch_black},
        std::vector<SDL_Texture*>{color_switch_white_hover, color_switch_black_hover},
        color_switch_pressed
    );
    PushButton board_flipper
    (
        SDL_Rect{320, 80, 200, 200}, SDL_Rect{0, 0, 32, 32},
        TOP_LEFT, FLIP_BOARD,
        board_flip, board_flip_hover, board_flip_pressed
    );
    buttons_gui.add(color_switcher);
    buttons_gui.add(board_flipper);

    buttons.add_gui(buttons_gui);

    // board_display.add_chess_tile();
}

DBvisualizer::~DBvisualizer()
{
    SDL_DestroyTexture(light_square);
    SDL_DestroyTexture(dark_square);
    SDL_DestroyTexture(background_t);
    SDL_DestroyTexture(color_switch_black);
    SDL_DestroyTexture(color_switch_white);
    SDL_DestroyTexture(color_switch_white_hover);
    SDL_DestroyTexture(color_switch_black_hover);
    SDL_DestroyTexture(color_switch_pressed);
    SDL_DestroyTexture(board_flip);
    SDL_DestroyTexture(board_flip_hover);
    SDL_DestroyTexture(board_flip_pressed);
}

std::vector<BUTTON_FUNCTION> DBvisualizer::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
    // sets the static variable `mouse_clicked` to see when the mouse transitions from unpressed to pressed.
    Button::is_mouse_clicked(key_pushes);

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