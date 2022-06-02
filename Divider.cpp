#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "GUI.hpp"
#include "Entity.hpp"

#include "Divider.hpp"


ChessTile::ChessTile(const Vector2f& p_pos, SDL_Texture* p_texture, SDL_Rect p_imgdata)
    :Entity(p_pos, Vector2f(1, 1), p_texture, p_imgdata, p_imgdata, TOP_CENTER), orig_pos(p_pos)
{}

ChessTile::~ChessTile()
{}


Divider::Divider(const SDL_Rect& p_border_box)
    :border_box(p_border_box)
{}

Divider::~Divider()
{}

std::vector<BUTTON_FUNCTION> Divider::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
    Vector2i divider_coords = Vector2i(border_box.x, border_box.y);

    Vector2i adj_mouse_coords = mouse_coords;
    adj_mouse_coords.x -= divider_coords.x;
    adj_mouse_coords.y -= divider_coords.y;

    std::vector<BUTTON_FUNCTION> functions;
    for(GUI& temp_gui : gui_list)
    {
        for(BUTTON_FUNCTION& temp_function : temp_gui.update(key_pushes, adj_mouse_coords, delta_time))
        {
            functions.push_back(temp_function);
        }
    }

    return functions;
}