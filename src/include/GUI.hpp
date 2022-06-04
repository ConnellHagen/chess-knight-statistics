#ifndef gui_h
#define gui_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <stdexcept>

#include "Math.hpp"
#include "utils.hpp"
#include "Text.hpp"


enum STATUS
{
	NONE,
	HOVER,
	PRESSED
};

struct Button
{
	Button(const SDL_Rect& p_original_box, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function);
	~Button();

	void build_border_box();
	static void is_mouse_clicked(const std::vector<bool>& key_pushes);

	static bool mouse_clicked;
	static bool mouse_held;

	Vector2f pos;
	SDL_Rect border_box;
	SDL_Rect original_box;
	RENDER_MODE render_mode;
	
	BUTTON_FUNCTION press_function;
};

struct PushButton : public Button
{
	PushButton(const SDL_Rect& p_original_box, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function, SDL_Texture* p_idle, SDL_Texture* p_hover, SDL_Texture* p_pressed);
	~PushButton();

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

	STATUS current_status;

	SDL_Texture* idle;
	SDL_Texture* hover;
	SDL_Texture* pressed;
};

struct ToggleButton : public Button
{
	ToggleButton(const SDL_Rect& p_original_box, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function, std::vector<SDL_Texture*> p_state_textures, std::vector<SDL_Texture*> p_state_hover_textures, SDL_Texture* p_pressed);
	~ToggleButton();

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);
	
	void toggle_state();

	int current_state;
	STATUS current_status;

	std::vector<SDL_Texture*> state_textures; 	    // textures for each standard state
	std::vector<SDL_Texture*> state_hover_textures; // textures for each hovered state
	SDL_Texture* pressed;
};

struct GUI
{
	GUI();
	~GUI();

	inline std::vector<Text> get_text_list(){ return text_list; }
	inline std::vector<ToggleButton> get_togbutton_list(){ return togbutton_list; }
	inline std::vector<PushButton> get_pushbutton_list(){ return pushbutton_list; }

	void add(const Text& p_text);
	void add(const ToggleButton& p_button);
	void add(const PushButton& p_button);

	std::vector<BUTTON_FUNCTION> update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time);

	std::vector<Text> text_list;
	std::vector<ToggleButton> togbutton_list;
	std::vector<PushButton> pushbutton_list;
};

#endif