
#include "sp_input_manager.h"

void SPInputManager::init() {
	memset(m_prev_keyboard_state, 0, 512);
	memset(m_cur_keyboard_state, 0, 512);
}

void SPInputManager::update() {
	int numkeys;
	const u8* buffer = SDL_GetKeyboardState(&numkeys);
	memcpy(m_prev_keyboard_state, m_cur_keyboard_state, numkeys);
	//Check events
	SDL_Event e;
	bool asdf = false;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_quit_event = true;
		}
	}
	memcpy(m_cur_keyboard_state, buffer, numkeys);

	m_prev_mouse_state[0] = m_cur_mouse_state[0];
	m_prev_mouse_state[1] = m_cur_mouse_state[1];

	u32 mouse_mask = SDL_GetMouseState(NULL, NULL);
	if (mouse_mask & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		m_cur_mouse_state[0] = true;
	}
	if (mouse_mask & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		m_cur_mouse_state[1] = true;
	}
}

void SPInputManager::shutdown() {
	// Nothing to see here
}

b32 SPInputManager::quitEvent() {
	return m_quit_event;
}

void SPInputManager::mousePos(int& x, int& y) {
	SDL_GetMouseState(&x, &y);
}

b32 SPInputManager::mouseLeftPressed() {
	if (m_cur_mouse_state[0] && !m_prev_mouse_state[0]) {
		return true;
	}
	return false;
}

b32 SPInputManager::mouseLeftHeld() {
	if ((m_cur_mouse_state[0] && !m_prev_mouse_state[0]) || (m_cur_mouse_state[0] && m_prev_mouse_state[0])) {
		return true;
	}
	return false;
}

b32 SPInputManager::mouseLeftReleased() {
	if (!m_cur_mouse_state[0] && m_prev_mouse_state[0]) {
		return true;
	}
	return false;
}

b32 SPInputManager::mouseRightPressed() {
	if (m_cur_mouse_state[1] && !m_prev_mouse_state[1]) {
		return true;
	}
	return false;
}

b32 SPInputManager::mouseRightHeld() {
	if ((m_cur_mouse_state[1] && !m_prev_mouse_state[1]) || (m_cur_mouse_state[1] && m_prev_mouse_state[1])) {
		return true;
	}
	return false;
}

b32 SPInputManager::mouseRightReleased() {
	if (!m_cur_mouse_state[1] && m_prev_mouse_state[1]) {
		return true;
	}
	return false;
}

b32 SPInputManager::keyboardCheckPressed(u8 key) {
	u8 prev = m_prev_keyboard_state[key];
	u8 cur = m_cur_keyboard_state[key];
	if (cur && !prev) {
		return true;
	}
	return false;
}

b32 SPInputManager::keyboardCheckHeld(u8 key) {
	u8 prev = m_prev_keyboard_state[key];
	u8 cur = m_cur_keyboard_state[key];
	if ((cur && !prev) || (cur && prev)) {
		return true;
	}
	return false;
}

b32 SPInputManager::keyboardCheckReleased(u8 key) {
	u8 prev = m_prev_keyboard_state[key];
	u8 cur = m_cur_keyboard_state[key];
	if (!cur && prev) {
		return true;
	}
	return false;
}