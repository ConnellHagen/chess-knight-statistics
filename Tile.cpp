#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Math.hpp"
#include "utils.hpp"

#include "Tile.hpp"


Tile::Tile(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture)
	:texture(p_texture), pos(p_pos), scale(p_scale)
{}

void Tile::set_texture(SDL_Texture* p_texture)
{
	texture = p_texture;
}

void Tile::set_scale(const Vector2f& p_scale)
{
	scale = p_scale;
}


Background::Background(const Vector2f& p_scale, SDL_Texture* p_texture)
	:texture(p_texture), scale(p_scale)
{
	make_tile_list();
}

Background::Background()
{}

void Background::make_tile_list()
{
	tile_list.clear();

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	const int tile_width = std::floor(scale.x * w);
	const int tile_height = std::floor(scale.y * h);

	const int horizontal_tiles = std::ceil(utils::ORIG_DISPLAY_WIDTH / static_cast<float>(tile_width));
	const int vertical_tiles = std::ceil(utils::ORIG_DISPLAY_HEIGHT / static_cast<float>(tile_height));

	for(int i = 0; i < horizontal_tiles; i++)
	{
		for(int j = 0; j < vertical_tiles; j++)
		{
			tile_list.push_back(Tile(Vector2f(i * tile_width, j * tile_height), scale, texture));
		}
	}
}

void Background::set_texture(SDL_Texture* p_texture)
{
	texture = p_texture;
	make_tile_list();
}

void Background::set_scale(const Vector2f& p_scale)
{
	scale = p_scale;
	make_tile_list();
}