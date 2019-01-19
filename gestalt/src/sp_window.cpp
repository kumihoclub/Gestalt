
#include "glad/glad.h"
#include "glad/src/glad.c"

#include "sp_window.h"

#include <algorithm>

void SPWindow::init(const char* title, SPViewport& viewport) {
	//memset(m_prev_keyboard_state, 0, 512);
	//memset(m_cur_keyboard_state, 0, 512);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, viewport.size.x, viewport.size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);
	m_context = SDL_GL_CreateContext(m_window);
	SDL_GL_SetSwapInterval(1);
	int x, y;
	SDL_GL_GetDrawableSize(m_window, &x, &y);
	viewport.size = { x, y };
	int res = gladLoadGLLoader(SDL_GL_GetProcAddress);
	glViewport(0, 0, viewport.size.x, viewport.size.y);
	glClearColor(0.175f, 0.225f, 0.250f, 1.0f);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SPWindow::shutdown() {
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

void SPWindow::update(SPViewport& viewport) {
	int x, y;
	SDL_GL_GetDrawableSize(m_window, &x, &y);
	viewport.scale = ((float)x / 960);
}

void SPWindow::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SPWindow::swap() {
	SDL_GL_SwapWindow(m_window);
}

void SPWindow::show() {
	SDL_ShowWindow(m_window);
}

void SPWindow::hide() {
	SDL_HideWindow(m_window);
}