#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "utils.hpp"
#include "Math.hpp"
#include "Text.hpp"

#include "GUI.hpp"


ToggleButton::ToggleButton(const Vector2f& p_pos, SDL_Texture* p_state1, SDL_Texture* p_state2, SDL_Texture* p_hover, SDL_Texture* p_pressed, const SDL_Rect& p_imgdata, const BUTTON_FUNCTION& p_press_function, const RENDER_MODE& p_render_mode)
	:pos(p_pos), render_mode(p_render_mode), current_state(STATE1), current_status(NONE), state1(p_state1), state2(p_state2), hover(p_hover), pressed(p_pressed), imgdata(p_imgdata), press_function(p_press_function)
{
	original_box = {static_cast<int>(pos.x), static_cast<int>(pos.y), imgdata.w, imgdata.h};
	build_border_box();
}

ToggleButton::~ToggleButton()
{}

std::vector<BUTTON_FUNCTION> ToggleButton::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
	std::vector<BUTTON_FUNCTION> functions;

	STATUS new_status = current_status;

	std::cout << mouse_coords.x << ", " << mouse_coords.y << "\n";
	std::cout << border_box.x << ", " << border_box.y << ", " << border_box.w << ", " << border_box.h << "\n";
	

	// sets `new_status` to the status of the button in this fram
	if(key_pushes[0] && contains_point(border_box, mouse_coords))
	{
		new_status = PRESSED;
	}
	else
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

void ToggleButton::build_border_box()
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


// GUI is the container of `Text`, `TextButton`s and other displayed non-entities.
// GUI must be containde in a `Divider`
GUI::GUI()
{}

GUI::~GUI()
{}

void GUI::add(const Text& p_text)
{
	text_list.push_back(p_text);
}

void GUI::add(const TextButton& p_textbutton)
{
	textbutton_list.push_back(p_textbutton);
}

void GUI::add(const ToggleButton& p_button)
{
	togbutton_list.push_back(p_button);
}

//accumulates all of the functions that the text buttons trigger whilst updating, and returns them in a vector
std::vector<BUTTON_FUNCTION> GUI::update(const std::vector<bool>& key_pushes, const Vector2i& mouse_coords, const float& delta_time)
{
	std::vector<BUTTON_FUNCTION> function_queue;

	for(TextButton& temp_text : textbutton_list)
	{
		for(BUTTON_FUNCTION& temp_function : temp_text.update(key_pushes, mouse_coords, delta_time))
		{
			function_queue.push_back(temp_function);
		}
	}

	for(ToggleButton& temp_button : togbutton_list)
	{
		for(BUTTON_FUNCTION& temp_function : temp_button.update(key_pushes, mouse_coords, delta_time))
		{
			function_queue.push_back(temp_function);
		}
	}
	
	return function_queue;
}