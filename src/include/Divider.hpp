#ifndef divider_h
#define divider_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "ChessTile.hpp"
#include "GUI.hpp"

class Divider
{
public:
    Divider(const SDL_Rect& p_border_box);
    virtual ~Divider() = 0;

    inline SDL_Rect get_border_box(){ return border_box; }

    virtual std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time) = 0;

protected:
    SDL_Rect border_box; 
};

class GUIDivider : public Divider
{
public:
    GUIDivider(const SDL_Rect& p_border_box);
    ~GUIDivider();

    inline std::vector<GUI> get_gui_list(){ return gui_list; }
    inline void add_gui(const GUI& p_gui){ gui_list.push_back(p_gui); }

    std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

private:
    std::vector<GUI> gui_list;
};

class ChessBoardDivider : public Divider
{
public:
    ChessBoardDivider(const SDL_Rect& p_border_box);
    ~ChessBoardDivider();

    inline std::vector<ChessTile> get_chess_tile_list(){ return chess_tile_list; }
    inline void add_chess_tile(const ChessTile& p_chess_tile){ chess_tile_list.push_back(p_chess_tile); }
    
    std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

private:
    std::vector<ChessTile> chess_tile_list;
};

#endif