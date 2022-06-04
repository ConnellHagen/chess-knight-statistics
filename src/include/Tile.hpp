#ifndef tile_h
#define tile_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Math.hpp"
#include "utils.hpp"


class Tile
{
public:
	Tile(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture);

	inline SDL_Rect get_original_image(){ return original_img; }
	
	inline Vector2f get_pos(){ return pos; }

	inline SDL_Texture* get_texture(){ return texture; }
	void set_texture(SDL_Texture* p_texture);

	inline Vector2f get_scale(){ return scale; }
	void set_scale(const Vector2f& p_scale);
	
private:
	SDL_Texture* texture;
	SDL_Rect original_img;
	Vector2f pos;
	Vector2f scale;
};

class Background
{
public:
	Background(const Vector2f& p_scale, SDL_Texture* p_texture);
	Background();

	void make_tile_list();

	inline std::vector<Tile> get_tile_list(){ return tile_list; }

	inline SDL_Texture* get_texture(){ return texture; }
	void set_texture(SDL_Texture* p_texture);

	inline Vector2f get_scale(){ return scale; }
	void set_scale(const Vector2f& p_scale);

private:
	SDL_Texture* texture;
	Vector2f scale;

	std::vector<Tile> tile_list;
};

#endif