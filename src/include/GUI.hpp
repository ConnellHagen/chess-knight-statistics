#ifndef gui_h
#define gui_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

#include "utils.hpp"
#include "Math.hpp"
#include "Text.hpp"

enum STATE
{
	STATE1, 
	STATE2
};

enum STATUS
{
	NONE,
	HOVER,
	PRESSED
};

struct ToggleButton
{
	ToggleButton(const Vector2f& p_pos, SDL_Texture* p_state1, SDL_Texture* p_state2, SDL_Texture* p_hover, SDL_Texture* p_pressed, const SDL_Rect& p_imgdata, const BUTTON_FUNCTION& p_press_function, const RENDER_MODE& p_render_mode);
	~ToggleButton();

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);
	
	void toggle_state();

	void build_border_box();

	Vector2f pos;
	SDL_Rect border_box;
	SDL_Rect original_box;
	RENDER_MODE render_mode;

	STATE current_state;
	STATUS current_status;

	SDL_Texture* state1;
	SDL_Texture* state2;
	SDL_Texture* hover;
	SDL_Texture* pressed;

	SDL_Rect imgdata;

	BUTTON_FUNCTION press_function;
};

struct GUI
{
	GUI();
	~GUI();

	inline std::vector<Text> get_text_list(){ return text_list; }
	inline std::vector<TextButton> get_textbutton_list(){ return textbutton_list; }
	inline std::vector<ToggleButton> get_togbutton_list(){ return togbutton_list; }

	void add(const Text& p_text);
	void add(const TextButton& p_textbutton);
	void add(const ToggleButton& p_button);

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

	std::vector<Text> text_list;
	std::vector<TextButton> textbutton_list;
	std::vector<ToggleButton> togbutton_list;
};

#endif