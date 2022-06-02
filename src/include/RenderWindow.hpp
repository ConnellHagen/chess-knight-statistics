#ifndef render_window_h
#define render_window_h

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils.hpp"
#include "Math.hpp"
#include "Tile.hpp"
#include "Text.hpp"
#include "Entity.hpp"
#include "GUI.hpp"
#include "Divider.hpp"


class RenderWindow
{
public:
	RenderWindow(const char* p_title, const int& p_w, const int& p_h);
	int get_refresh_rate();

	SDL_Texture* load_texture(const char* p_filePath);

	void clear();

	void render(Entity p_entity);
	void render(Background& p_background);
	void render(Tile& p_tile);
	void render(Text& p_text);
	void render(Divider& p_divider);

	void display();

	inline SDL_Renderer* get_renderer(){return renderer;}
	inline SDL_Window* get_window(){return window;}
	
	void clean_up();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif