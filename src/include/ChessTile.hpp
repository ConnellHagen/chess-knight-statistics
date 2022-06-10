#ifndef chesstile_h
#define chesstile_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"


struct ChessTile : public Entity
{
    ChessTile(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture);
    ~ChessTile();

    inline void reset_position(){ Entity::set_pos(orig_pos); }

    Vector2f orig_pos;
    Vector2f scale;
};

#endif