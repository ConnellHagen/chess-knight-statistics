#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils.hpp"
#include "Math.hpp"
#include "Tile.hpp"
#include "Text.hpp"
#include "GUI.hpp"
#include "Divider.hpp"

#include "RenderWindow.hpp"


RenderWindow::RenderWindow(const char* p_title, const int& p_w, const int& p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	if(window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << "\n";
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::load_texture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if(texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << "\n";

	return texture;
}
 
int RenderWindow::get_refresh_rate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	
	return mode.refresh_rate;
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity p_entity)
{
	SDL_Rect src;
	src.x = p_entity.get_sprite_frame().x;
	src.y = p_entity.get_sprite_frame().y;
	src.w = p_entity.get_sprite_frame().w;
	src.h = p_entity.get_sprite_frame().h;

	SDL_Rect dst = p_entity.get_border_box();
	dst.x *= utils::get_scale().x;
	dst.y *= utils::get_scale().y;
	dst.w *= utils::get_scale().x;
	dst.h *= utils::get_scale().y;

	SDL_RenderCopyEx(renderer, p_entity.get_texture(), &src, &dst, /*static_cast<double>(p_entity.get_angle())*/0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::render(Background& p_background)
{
	std::vector<Tile> render_list = p_background.get_tile_list();
	for(Tile background_tile : render_list)
	{
		render(background_tile);
	}
}

void RenderWindow::render(Tile& p_tile)
{
	SDL_Rect src;
	src.x = p_tile.get_original_image().x;
	src.y = p_tile.get_original_image().y;
	src.w = p_tile.get_original_image().w;
	src.h = p_tile.get_original_image().h;

	SDL_Rect dst;
	dst.x = p_tile.get_pos().x * utils::get_scale().x;
	dst.y = p_tile.get_pos().y * utils::get_scale().y;
	dst.w = std::ceil(p_tile.get_original_image().w * p_tile.get_scale().x * utils::get_scale().x);
	dst.h = std::ceil(p_tile.get_original_image().h * p_tile.get_scale().y * utils::get_scale().y);

	SDL_RenderCopy(renderer, p_tile.get_texture(), &src, &dst);
}

void RenderWindow::render(Text& p_text)
{
	SDL_Rect src = p_text.border_box;
	src.x = 0;
	src.y = 0;

	SDL_Rect dst = p_text.border_box;
	dst.x *= utils::get_scale().x;
	dst.y *= utils::get_scale().y;
	dst.w *= utils::get_scale().x;
	dst.h *= utils::get_scale().y;

	SDL_RenderCopyEx(renderer, p_text.texture, &src, &dst, 0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::render(TextButton& p_text)
{
	render(p_text.text);
}

void RenderWindow::render(Divider& p_divider)
{
	for(GUI& gui : p_divider.get_gui_list())
	{
		for(Text& temp_text : gui.get_text_list())
		{
			// this is probably wrong i havent tested it and it should be imgdata i think
			SDL_Rect src;
			src.x = temp_text.border_box.x;
			src.y = temp_text.border_box.y;
			src.w = temp_text.border_box.w;
			src.h = temp_text.border_box.h;

			SDL_Rect dst = temp_text.border_box;
			dst.x = (dst.x + p_divider.get_border_box().x) * utils::get_scale().x;
			dst.y = (dst.y + p_divider.get_border_box().y) * utils::get_scale().y;
			dst.w *= utils::get_scale().x;
			dst.h *= utils::get_scale().y;

			SDL_RenderCopyEx(renderer, temp_text.texture, &src, &dst, 0, NULL, SDL_FLIP_NONE);
		}

		for(TextButton& temp_text : gui.get_textbutton_list())
		{
			// same for this one
			SDL_Rect src = temp_text.text.border_box;

			SDL_Rect dst = temp_text.text.border_box;
			dst.x = (dst.x + p_divider.get_border_box().x) * utils::get_scale().x;
			dst.y = (dst.y + p_divider.get_border_box().y) * utils::get_scale().y;
			dst.w *= utils::get_scale().x;
			dst.h *= utils::get_scale().y;

			SDL_RenderCopyEx(renderer, temp_text.text.texture, &src, &dst, 0, NULL, SDL_FLIP_NONE);
		}

		for(ToggleButton& temp_button : gui.get_togbutton_list())
		{
			SDL_Rect src = temp_button.imgdata;

			SDL_Rect dst = temp_button.border_box;
			dst.x = (dst.x + p_divider.get_border_box().x) * utils::get_scale().x;
			dst.y = (dst.y + p_divider.get_border_box().y) * utils::get_scale().y;
			dst.w *= utils::get_scale().x;
			dst.h *= utils::get_scale().y;

			SDL_Texture* texture_in_use = nullptr;
			switch(temp_button.current_status)
			{
			case HOVER:
				texture_in_use = temp_button.hover;
				break;

			case PRESSED:
				texture_in_use = temp_button.pressed;
				break;

			case NONE:
				switch(temp_button.current_state)
				{
				case STATE1:
					texture_in_use = temp_button.state1;
					break;
				case STATE2:
					texture_in_use = temp_button.state2;
					break;
				}
				break;
			}

			SDL_RenderCopyEx(renderer, texture_in_use, &src, &dst, 0, NULL, SDL_FLIP_NONE);
		}
	}

	for(ChessTile& chess_tile : p_divider.get_chess_tile_list())
	{
		render(static_cast<Entity>(chess_tile));
	}
}
	
void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::clean_up()
{
	SDL_DestroyWindow(window);
}
