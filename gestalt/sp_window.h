#pragma once

#include "sp_common.h"
#include "sp_renderable.h"
#include "sp_viewport.h"

#include "SDL2/SDL.h"

class SPWindow {
public:
	void init(const char* title, SPViewport& viewport);
	void shutdown();
	void update(SPViewport& viewport);
	void clear();
	void swap();
	void show();
	void hide();
	b32 quitEvent();

private:
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_context;

};