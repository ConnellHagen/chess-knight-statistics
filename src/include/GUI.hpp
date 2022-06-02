#ifndef gui_h
#define gui_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "Math.hpp"
#include "utils.hpp"
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

struct Button
{
	Button(const SDL_Rect& p_original_box, const SDL_Rect& p_imgdata, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function);
	~Button();

	void build_border_box();
	static void is_mouse_clicked(const std::vector<bool>& key_pushes);

	static bool mouse_clicked;
	static bool mouse_held;

	Vector2f pos;
	SDL_Rect border_box;
	SDL_Rect original_box;
	RENDER_MODE render_mode;
	
	SDL_Rect imgdata;

	BUTTON_FUNCTION press_function;
};

struct PushButton : public Button
{
	PushButton(const SDL_Rect& p_original_box, const SDL_Rect& p_imgdata, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function, SDL_Texture* p_idle, SDL_Texture* p_hover, SDL_Texture* p_pressed);
	~PushButton();

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

	STATUS current_status;

	SDL_Texture* idle;
	SDL_Texture* hover;
	SDL_Texture* pressed;
};

struct ToggleButton : public Button
{
	ToggleButton(const SDL_Rect& p_original_box, const SDL_Rect& p_imgdata, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function, SDL_Texture* p_state1, SDL_Texture* p_state2, SDL_Texture* p_state1_hover, SDL_Texture* p_state2_hover, SDL_Texture* p_pressed);
	~ToggleButton();

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);
	
	void toggle_state();

	STATE current_state;
	STATUS current_status;

	SDL_Texture* state1;
	SDL_Texture* state2;
	SDL_Texture* state1_hover;
	SDL_Texture* state2_hover;
	SDL_Texture* pressed;
};

struct GUI
{
	GUI();
	~GUI();

	inline std::vector<Text> get_text_list(){ return text_list; }
	inline std::vector<ToggleButton> get_togbutton_list(){ return togbutton_list; }

	void add(const Text& p_text);
	void add(const ToggleButton& p_button);

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

	std::vector<Text> text_list;
	std::vector<ToggleButton> togbutton_list;
};

#endif