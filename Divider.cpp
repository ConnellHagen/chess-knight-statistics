#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Entity.hpp"
#include "ChessTile.hpp"
#include "GUI.hpp"

#include "Divider.hpp"


Divider::Divider(const SDL_Rect& p_border_box)
    :border_box(p_border_box)
{}

// apparently you need to define a virtual destructor ??
Divider::~Divider()
{}

GUIDivider::GUIDivider(const SDL_Rect& p_border_box)
    :Divider(p_border_box)
{}

GUIDivider::~GUIDivider()
{}

std::vector<BUTTON_FUNCTION> GUIDivider::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
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

ChessBoardDivider::ChessBoardDivider(const SDL_Rect& p_border_box)
    :Divider(p_border_box)
{}

ChessBoardDivider::~ChessBoardDivider()
{}

std::vector<BUTTON_FUNCTION> ChessBoardDivider::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
    std::vector<BUTTON_FUNCTION> functions;

    // possible (?) functions include clicking on a square making it display 

    return functions;
}
