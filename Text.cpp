#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Math.hpp"
#include "utils.hpp"

#include "Text.hpp"


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