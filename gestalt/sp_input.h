#pragma once

#include "sp_common.h"

#include "SDL2/SDL.h"

// src in "sp_window.cpp"

class SPKeyboardKey {
public:
	SPKeyboardKey(u8 key);
	b32 pressed();
	b32 held();
	b32 released();
private:
	u8 m_key = SDL_SCANCODE_UNKNOWN;
};