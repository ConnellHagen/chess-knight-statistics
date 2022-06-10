#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ChessTile.hpp"


ChessTile::ChessTile(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture)
    :Entity(p_pos, p_scale, p_texture, TOP_CENTER), orig_pos(p_pos), scale(p_scale)
{}

ChessTile::~ChessTile()
{}