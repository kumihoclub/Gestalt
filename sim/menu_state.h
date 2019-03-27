#pragma once

#include "sp_render_text.h"
#include "sp_input.h"
#include "sp_transition.h"

#include "sp_state.h"

class MenuState : public SPState {
public:
	void onEnter();
	void update(SPViewport& view, SPFrame& frame, SPTransitionStack* transition_stack);
	void onExit();

private:
	SPCamera m_camera;
	SPRenderText m_menu_text;
	SPRenderText m_press_space_text;
	SPKeyboardKey m_space = SPKeyboardKey(SDL_SCANCODE_SPACE);

};