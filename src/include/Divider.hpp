#ifndef divider_h
#define divider_h

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GUI.hpp"
#include "Entity.hpp"

struct ChessTile : public Entity
{
    ChessTile(const Vector2f& p_pos, SDL_Texture* p_texture, SDL_Rect p_imgdata);
    ~ChessTile();

    inline void reset_position(){ Entity::set_pos(orig_pos); }

    Vector2f orig_pos;
};

class Divider
{
public:
    Divider(const SDL_Rect& p_border_box);
    ~Divider();

    inline SDL_Rect get_border_box(){ return border_box; }
    inline std::vector<GUI> get_gui_list(){ return gui_list; }
    inline std::vector<ChessTile> get_chess_tile_list(){ return chess_tile_list; }

    inline void add_gui(const GUI& p_gui){ gui_list.push_back(p_gui); }
    inline void add_chess_tile(const ChessTile& p_chess_tile){ chess_tile_list.push_back(p_chess_tile); }

    std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

private:
    SDL_Rect border_box;
    std::vector<GUI> gui_list;
    std::vector<ChessTile> chess_tile_list;
};

#endif