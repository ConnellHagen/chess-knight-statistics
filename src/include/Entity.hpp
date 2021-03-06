#ifndef entity_h
#define entity_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "utils.hpp"
#include "Math.hpp"


class Entity
{
public:
	Entity(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture, const SDL_Rect& p_sheet, const SDL_Rect& p_current, const RENDER_MODE& p_render_mode);
	Entity(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture, const RENDER_MODE& p_render_mode);

	inline Vector2f get_pos(){ return pos; }
	void set_pos(const Vector2f& p_pos);
	
	Vector2f get_center();

	inline Vector2f& get_scale(){ return scale; }
	void set_scale(const float& p_w, const float& p_h);

	inline SDL_Texture* get_texture(){ return texture; }

	inline SDL_Rect get_sprite_frame(){ return current_sprite_frame; }
	inline void set_sprite_frame(const SDL_Rect& p_imgdata){ current_sprite_frame = p_imgdata; }

	inline SDL_Rect get_border_box(){ return border_box; }

	inline int get_render_mode(){ return render_mode; }

	void next_sprite_frame();
	
protected:
	SDL_Texture* texture;
	Vector2f pos;
	Vector2f scale;

	RENDER_MODE render_mode;
	SDL_Rect border_box;

private:
	SDL_Rect sprite_sheet;
	SDL_Rect current_sprite_frame;
	
	void build_border_box();
};

#endif