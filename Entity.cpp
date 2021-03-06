#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "utils.hpp"

#include "Entity.hpp"


Entity::Entity(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture, const SDL_Rect& p_sheet, const SDL_Rect& p_current, const RENDER_MODE& p_render_mode)
	:sprite_sheet(p_sheet), current_sprite_frame(p_current), texture(p_texture), pos(p_pos), scale(p_scale), render_mode(p_render_mode)
{
	build_border_box();
}

Entity::Entity(const Vector2f& p_pos, const Vector2f& p_scale, SDL_Texture* p_texture, const RENDER_MODE& p_render_mode)
	:texture(p_texture), pos(p_pos), scale(p_scale), render_mode(p_render_mode)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	current_sprite_frame = sprite_sheet = SDL_Rect{0, 0, w, h};

	build_border_box();
}

void Entity::set_pos(const Vector2f& p_pos)
{
	pos = p_pos;
	build_border_box();
}

Vector2f Entity::get_center()
{
	float temp_x = border_box.x + border_box.w/2;
	float temp_y = border_box.y + border_box.h/2;
	return Vector2f(temp_x, temp_y);
}

void Entity::set_scale(const float& p_w, const float& p_h)
{
	scale = Vector2f(p_w, p_h);
	build_border_box();
}

void Entity::build_border_box()
{
	SDL_Rect new_border = current_sprite_frame;
	new_border.x = pos.x;
	new_border.y = pos.y;
	new_border.w *= scale.x;
	new_border.h *= scale.y;

	switch(render_mode)
	{
	case TOP_LEFT:
		break;
	case TOP_CENTER:
		new_border.x -= current_sprite_frame.w/2 * scale.x;
		break;
	case TOP_RIGHT:
		new_border.x -= current_sprite_frame.w * scale.x;
		break;
	case MIDDLE_LEFT:
		new_border.y -= current_sprite_frame.h/2 * scale.y;
		break;
	case MIDDLE_CENTER:
		new_border.x -= current_sprite_frame.w/2 * scale.x;
		new_border.y -= current_sprite_frame.h/2 * scale.y;
		break;
	case MIDDLE_RIGHT:
		new_border.x -= current_sprite_frame.w * scale.x;
		new_border.y -= current_sprite_frame.h/2 * scale.y;
		break;
	case BOTTOM_LEFT:
		new_border.y -= current_sprite_frame.h * scale.y;
		break;
	case BOTTOM_CENTER:
		new_border.x -= current_sprite_frame.w/2 * scale.x;
		new_border.y -= current_sprite_frame.h * scale.y;
		break;
	case BOTTOM_RIGHT:
		new_border.x -= current_sprite_frame.w * scale.x;
		new_border.y -= current_sprite_frame.h * scale.y;
		break;
	}

	border_box = new_border;
}

void Entity::next_sprite_frame()
{
	if(current_sprite_frame.x + current_sprite_frame.h == sprite_sheet.w)
	{
		if(current_sprite_frame.y + current_sprite_frame.h == sprite_sheet.h)
		{
			current_sprite_frame.x = 0;
			current_sprite_frame.y = 0;
			return;
		}
		current_sprite_frame.x = 0;
		current_sprite_frame.y += current_sprite_frame.h;
		return;
	}
	current_sprite_frame.x += current_sprite_frame.w;
}
