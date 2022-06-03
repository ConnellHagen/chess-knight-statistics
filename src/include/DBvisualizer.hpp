#ifndef dbvisualizer_h
#define dbvisualizer_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils.hpp"
#include "Tile.hpp"
#include "GUI.hpp"
#include "Divider.hpp"
#include "RenderWindow.hpp"


class DBvisualizer
{
public:
    DBvisualizer(RenderWindow* window);
    ~DBvisualizer();

    std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

    void render();

private:
    RenderWindow* window;

    SDL_Texture* background_t;
    SDL_Rect background_inf;
    Background background;

    SDL_Texture* light_square;
    SDL_Texture* dark_square;

    SDL_Texture* color_switch_white;
    SDL_Texture* color_switch_black;
    SDL_Texture* color_switch_white_hover;
    SDL_Texture* color_switch_black_hover;
    SDL_Texture* color_switch_pressed;

    SDL_Texture* board_flip;
    SDL_Texture* board_flip_hover;
    SDL_Texture* board_flip_pressed;

    Divider board_display;
    Divider buttons;
};

#endif