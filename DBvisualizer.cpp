#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils.hpp"
#include "Tile.hpp"
#include "ChessTile.hpp"
#include "GUI.hpp"
#include "Divider.hpp"
#include "RenderWindow.hpp"

#include "DBVisualizer.hpp"


DBVisualizer::DBVisualizer(RenderWindow* p_window)
    :window(p_window), board_display(SDL_Rect{0, 0, 1080, 1080}), buttons(SDL_Rect{1080, 0, 840, 1080})
{
    // loading background and textures
    background_t = window->load_texture("img/background.png");

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

    square_ignore_off = window->load_texture("img/buttons/square-ignore-off.png");
    square_ignore_on = window->load_texture("img/buttons/square-ignore-on.png");
    square_ignore_off_hover = window->load_texture("img/buttons/square-ignore-off-hover.png");
    square_ignore_on_hover = window->load_texture("img/buttons/square-ignore-on-hover.png");
    square_ignore_pressed = window->load_texture("img/buttons/square-ignore-pressed.png");


    background = Background(Vector2f(1, 1), background_t);

    GUI buttons_gui;

    ToggleButton color_switcher
    (
        SDL_Rect{80, 80, 200, 200}, TOP_LEFT, SWITCH_COLORS,
        std::vector<SDL_Texture*>{color_switch_white, color_switch_black},
        std::vector<SDL_Texture*>{color_switch_white_hover, color_switch_black_hover},
        color_switch_pressed
    );
    PushButton board_flipper
    (
        SDL_Rect{320, 80, 200, 200}, TOP_LEFT, FLIP_BOARD,
        board_flip, board_flip_hover, board_flip_pressed
    );
    ToggleButton starting_square_ignorer
    (
        SDL_Rect{560, 80, 200, 200}, TOP_LEFT, TOGGLE_STARTING_SQUARE_IGNORE,
        std::vector<SDL_Texture*>{square_ignore_off, square_ignore_on},
        std::vector<SDL_Texture*>{square_ignore_off_hover, square_ignore_on_hover},
        square_ignore_pressed
    );

    buttons_gui.add(color_switcher);
    buttons_gui.add(board_flipper);
    buttons_gui.add(starting_square_ignorer);

    buttons.add_gui(buttons_gui);

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Vector2f tile_pos;
            const Vector2f tile_scale(4, 4);

            int w;
            SDL_QueryTexture(light_square, NULL, NULL, &w, NULL);
            const int tile_width = w * tile_scale.x;

            const Vector2f i_vec(1.0f * tile_width / 2, 0.5f * tile_width / 2);
            const Vector2f j_vec(-1.0f * tile_width / 2, 0.5f * tile_width / 2);

            // translation from chessboard coords (0-7, 0-7) to the on screen diagonal board
            tile_pos.x = i_vec.x * i + j_vec.x * j;
            tile_pos.y = i_vec.y * i + j_vec.y * j;

            tile_pos.x += board_display.get_border_box().w / 2;
            tile_pos.y += board_display.get_border_box().h / 2;

            board_display.add_chess_tile(ChessTile(tile_pos, tile_scale, (i + j) % 2 == 0 ? light_square : dark_square));
        }
    }
}

DBVisualizer::~DBVisualizer()
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
    SDL_DestroyTexture(square_ignore_off);
    SDL_DestroyTexture(square_ignore_on);
    SDL_DestroyTexture(square_ignore_off_hover);
    SDL_DestroyTexture(square_ignore_on_hover);
    SDL_DestroyTexture(square_ignore_pressed);
}

std::vector<BUTTON_FUNCTION> DBVisualizer::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
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

void DBVisualizer::render()
{
    window->render(background);
    window->render(board_display);
    window->render(buttons);
}