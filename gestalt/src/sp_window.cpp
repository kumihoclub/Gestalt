
#include "glad/glad.h"
#include "glad/src/glad.c"

#include "sp_window.h"
#include "sp_input.h"

#include <algorithm>

namespace {
	u8 prev_keyboard_state[SDL_NUM_SCANCODES];
	u8 cur_keyboard_state[SDL_NUM_SCANCODES];
	u8 prev_mouse_state[2];
	u8 cur_mouse_state[2];
	b32 quit_event = false;

}

SPKeyboardKey::SPKeyboardKey(u8 key) {
	m_key = key;
}

b32 SPKeyboardKey::pressed() {
	u8 prev = prev_keyboard_state[m_key];
	u8 cur = cur_keyboard_state[m_key];
	if (cur && !prev) {
		return true;
	}
	return false;
}

b32 SPKeyboardKey::held() {
	u8 prev = prev_keyboard_state[m_key];
	u8 cur = cur_keyboard_state[m_key];
	if ((cur && !prev) || (cur && prev)) {
		return true;
	}
	return false;
}

b32 SPKeyboardKey::released() {
	u8 prev = prev_keyboard_state[m_key];
	u8 cur = cur_keyboard_state[m_key];
	if (!cur && prev) {
		return true;
	}
	return false;
}

void SPWindow::init(const char* title, SPViewport& viewport) {
	m_initial_view = viewport;
	m_initial_view.scale = 1.0f; // Scale on initialization should always be 1.0
	m_cur_view = m_initial_view;
	memset(prev_keyboard_state, 0, SDL_NUM_SCANCODES);
	memset(cur_keyboard_state, 0, SDL_NUM_SCANCODES);
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
	//glClearColor(0.175f, 0.225f, 0.250f, 1.0f);
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

	if (m_cur_view.scale != viewport.scale) {
		m_cur_view = viewport;
		SDL_SetWindowSize(m_window, (int)m_cur_view.size.x * m_cur_view.scale, (int)m_cur_view.size.y * m_cur_view.scale);
		glViewport(0, 0, m_cur_view.size.x * m_cur_view.scale, m_cur_view.size.y * m_cur_view.scale);
		SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}

	// Update input
	int numkeys;
	const u8* buffer = SDL_GetKeyboardState(&numkeys);
	memcpy(prev_keyboard_state, cur_keyboard_state, numkeys);
	SDL_Event e;
	bool asdf = false;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			quit_event = true;
		}
	}
	memcpy(cur_keyboard_state, buffer, numkeys);

	prev_mouse_state[0] = cur_mouse_state[0];
	prev_mouse_state[1] = cur_mouse_state[1];

	u32 mouse_mask = SDL_GetMouseState(NULL, NULL);
	if (mouse_mask & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		cur_mouse_state[0] = true;
	}
	if (mouse_mask & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		cur_mouse_state[1] = true;
	}
}

void SPWindow::clear() {
	glClearColor(0.175f, 0.225f, 0.250f, 1.0f);
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

b32 SPWindow::quitEvent() {
	return quit_event;
}