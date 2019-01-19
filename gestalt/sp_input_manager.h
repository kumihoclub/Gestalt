#pragma once

#include "sp_common.h"

#include "SDL2/SDL.h"

class SPInputManager {
public:
	void init();
	void update();
	void shutdown();
	b32 quitEvent();
	void mousePos(int& x, int& y);
	b32 mouseLeftPressed();
	b32 mouseLeftHeld();
	b32 mouseLeftReleased();
	b32 mouseRightPressed();
	b32 mouseRightHeld();
	b32 mouseRightReleased();
	b32 keyboardCheckPressed(u8 key);
	b32 keyboardCheckHeld(u8 key);
	b32 keyboardCheckReleased(u8 key);

private:
	b32 m_quit_event = false;
	u8 m_prev_keyboard_state[SDL_NUM_SCANCODES];
	u8 m_cur_keyboard_state[SDL_NUM_SCANCODES];
	u8 m_prev_mouse_state[2];
	u8 m_cur_mouse_state[2];

};