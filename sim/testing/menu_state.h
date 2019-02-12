#pragma once

#include "sp_render_text.h"
#include "sp_input.h"

#include "bt_state.h"

class MenuState : public BTState {
public:
	void onEnter();
	void update(SPViewport& view, SPFrame& frame, BTTransitionStack* transition_stack);
	void onExit();

private:
	SPCamera m_camera;
	SPRenderText m_menu_text;
	SPKeyboardKey m_space = SPKeyboardKey(SDL_SCANCODE_SPACE);

};