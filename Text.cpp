#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>

#include "utils.hpp"
#include "Text.hpp"
#include "Math.hpp"

Text::Text(SDL_Renderer* p_renderer, const RENDER_MODE& p_render_mode, const std::string& p_font_path, const int& p_size, const SDL_Color& p_color, const std::string& p_text, const Vector2f& p_pos)
	:renderer(p_renderer), render_mode(p_render_mode), font_path(p_font_path), size(p_size), color(p_color), text(p_text), pos(p_pos)
{
	font = TTF_OpenFont(font_path.c_str(), size);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	original_box = SDL_Rect{static_cast<int>(pos.x), static_cast<int>(pos.y), surface->w, surface->h};
	build_border_box();

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}
	
Text::~Text()
{
	// SDL_DestroyTexture(texture);
	// TTF_CloseFont(font);
}

void Text::resize_font(const int& p_size)
{
	size = p_size;

	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);

	font = TTF_OpenFont(font_path.c_str(), size);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	original_box = SDL_Rect{static_cast<int>(pos.x), static_cast<int>(pos.y), surface->w, surface->h};
	build_border_box();

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}

void Text::recolor_font(const SDL_Color& p_color)
{
	color = p_color;
	
	SDL_DestroyTexture(texture);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}

void Text::change_text(const std::string& p_text)
{
	text = p_text;

	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);

	font = TTF_OpenFont(font_path.c_str(), size);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	original_box = SDL_Rect{static_cast<int>(pos.x), static_cast<int>(pos.y), surface->w, surface->h};
	build_border_box();

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

}

void Text::change_render_mode(const RENDER_MODE& p_render_mode)
{
	render_mode = p_render_mode;

	build_border_box();
}


void Text::build_border_box()
{
	SDL_Rect new_border = original_box;

	switch(render_mode)
	{
	case TOP_LEFT:
		break;
	case TOP_CENTER:
		new_border.x -= original_box.w/2;
		break;
	case TOP_RIGHT:
		new_border.x -= original_box.w;
		break;
	case MIDDLE_LEFT:
		new_border.y -= original_box.h/2;
		break;
	case MIDDLE_CENTER:
		new_border.x -= original_box.w/2;
		new_border.y -= original_box.h/2;
		break;
	case MIDDLE_RIGHT:
		new_border.x -= original_box.w;
		new_border.y -= original_box.h/2;
		break;
	case BOTTOM_LEFT:
		new_border.y -= original_box.h;
		break;
	case BOTTOM_CENTER:
		new_border.x -= original_box.w/2;
		new_border.y -= original_box.h;
		break;
	case BOTTOM_RIGHT:
		new_border.x -= original_box.w;
		new_border.y -= original_box.h;
		break;
	}

	border_box = new_border;
}

TextButton::TextButton(const Text& p_text, const SDL_Color& p_hover_color, const BUTTON_FUNCTION& p_press_function)
	:text(p_text), current_state(UNPRESSED), default_color(p_text.color), hover_color(p_hover_color), press_color(SDL_Color{255, 255, 255, 255})
{}

TextButton::TextButton(const Text& p_text, const SDL_Color& p_hover_color, const SDL_Color& p_press_color, const BUTTON_FUNCTION& p_press_function)
	:text(p_text), current_state(UNPRESSED), default_color(p_text.color), hover_color(p_hover_color), press_color(p_press_color), press_function(p_press_function)
{}

TextButton::~TextButton()
{}

std::vector<BUTTON_FUNCTION> TextButton::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
	std::vector<BUTTON_FUNCTION> functions;

	color_state new_state = current_state;

	// checks if the button has changed its state in the last frame
	if(new_state != PRESSED && key_pushes[4] && contains_point(text.border_box, mouse_coords))
	{
		new_state = PRESSED;
	}
	else if(new_state == PRESSED && !key_pushes[4])
	{
		new_state = contains_point(text.border_box, mouse_coords)? HOVER : UNPRESSED;
	}
	else if(new_state != PRESSED)
	{
		new_state = contains_point(text.border_box, mouse_coords)? HOVER : UNPRESSED;
	}
	
	// if it has changed states, then makes the necessary changes
	// first block of code is for if the button is being held/released, activating the co-responding function
	// the second is for changing the color if it isn't being pressed
	if(new_state == PRESSED && current_state != PRESSED) // pressed button
	{
		text.recolor_font(press_color);
		current_state = PRESSED;
	}
	else if(new_state != PRESSED && current_state == PRESSED) // released button
	{
		functions.push_back(press_function);
	}

	if(new_state != PRESSED)
	{
		if(new_state == HOVER)
		{
			text.recolor_font(hover_color);
			current_state = HOVER;
		}
		else
		{
			text.recolor_font(default_color);
			current_state = UNPRESSED;
		}
	}

	return functions;
}