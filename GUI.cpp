#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "Math.hpp"
#include "utils.hpp"
#include "Text.hpp"

#include "GUI.hpp"


Button::Button(const SDL_Rect& p_original_box, const SDL_Rect& p_imgdata, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function)
	:original_box(p_original_box), imgdata(p_imgdata), render_mode(p_render_mode), press_function(p_press_function)
{
	build_border_box();
}

Button::~Button()
{}

void Button::build_border_box()
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

void Button::is_mouse_clicked(const std::vector<bool>& key_pushes)
{
	if(!key_pushes[0])
	{
		mouse_clicked = false;
		mouse_held = false;
	}
	else if(mouse_clicked) 
	{
		mouse_clicked = false;
	}
	else if(!mouse_held)
	{
		mouse_clicked = true;
		mouse_held = true;
	}
}


PushButton::PushButton(const SDL_Rect& p_original_box, const SDL_Rect& p_imgdata, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function, SDL_Texture* p_idle, SDL_Texture* p_hover, SDL_Texture* p_pressed)
	:Button(p_original_box, p_imgdata, p_render_mode, p_press_function), idle(p_idle), hover(p_hover), pressed(p_pressed)
{}

PushButton::~PushButton()
{}

std::vector<BUTTON_FUNCTION> PushButton::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{}


// buttons which toggle between a number of states upon click
ToggleButton::ToggleButton(const SDL_Rect& p_original_box, const SDL_Rect& p_imgdata, const RENDER_MODE& p_render_mode, const BUTTON_FUNCTION& p_press_function, SDL_Texture* p_state1, SDL_Texture* p_state2, SDL_Texture* p_state1_hover, SDL_Texture* p_state2_hover, SDL_Texture* p_pressed)
	:Button(p_original_box, p_imgdata, p_render_mode, p_press_function), state1(p_state1), state2(p_state2), state1_hover(p_state1_hover), state2_hover(p_state2_hover), pressed(p_pressed)
{
	Button::build_border_box();

	current_state = STATE1;
}

ToggleButton::~ToggleButton()
{}

std::vector<BUTTON_FUNCTION> ToggleButton::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
	std::vector<BUTTON_FUNCTION> functions;

	STATUS new_status = current_status;

	// sets `new_status` to the status of the button in this fram
	if(Button::mouse_clicked && contains_point(border_box, mouse_coords))
	{
		new_status = PRESSED;
	}
	else if(!key_pushes[0])
	{
		new_status = contains_point(border_box, mouse_coords) ? HOVER : NONE;
	}
	
	// if it has changed states, then makes the necessary changes
	if(new_status == PRESSED && current_status != PRESSED) // pressed button
	{
		current_status = PRESSED;
	}
	else if(new_status != PRESSED && current_status == PRESSED) // released button
	{
		toggle_state();
		functions.push_back(press_function);
	}

	current_status = new_status;
	
	return functions;
}

void ToggleButton::toggle_state()
{
	if(current_state == STATE1)
	{
		current_state = STATE2;
	}
	else if (current_state == STATE2)
	{
		current_state = STATE1;
	}
}


// GUI is the container of `Text`, `Button`s and other displayed non-entities.
// GUI must be containde in a `Divider`
GUI::GUI()
{}

GUI::~GUI()
{}

void GUI::add(const Text& p_text)
{
	text_list.push_back(p_text);
}

void GUI::add(const ToggleButton& p_button)
{
	togbutton_list.push_back(p_button);
}

//accumulates all of the functions that the text buttons trigger whilst updating, and returns them in a vector
std::vector<BUTTON_FUNCTION> GUI::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
	std::vector<BUTTON_FUNCTION> function_queue;

	for(ToggleButton& temp_button : togbutton_list)
	{
		for(BUTTON_FUNCTION& temp_function : temp_button.update(key_pushes, mouse_coords, delta_time))
		{
			function_queue.push_back(temp_function);
		}
	}
	
	return function_queue;
}