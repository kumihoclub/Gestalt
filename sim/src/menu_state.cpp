
#include "menu_state.h"
#include "game_state.h"

void MenuState::onEnter() {
	m_menu_text.set("Main Menu State");
	m_menu_text.transform.scale = { 0.8f, 0.8f };
	m_menu_text.transform.anchor = SP_ANCHOR_VIEWPORT;
	m_menu_text.transform.pos = { 0.0f, 0.1f };
	m_menu_text.transform.origin = { 0.0f, 0.0f };
	m_press_space_text.set("Press space to enter the \"Game State\"");
	m_press_space_text.transform.scale = { 0.25f, 0.25f };
	m_press_space_text.transform.anchor = SP_ANCHOR_VIEWPORT;
	m_press_space_text.transform.pos = { 0.0f, -0.25f };
	m_press_space_text.transform.origin = { 0.0f, 0.0f };
}

void MenuState::update(SPViewport& view, SPFrame& frame, SPTransitionStack* transition_stack) {
	if (m_space.pressed()) {
		GameState* test = new GameState();
		SPTransition transition;
		transition.type = SP_TRANSITION_TYPE_PUSH_PRESERVE;
		transition.state = test;
		transition_stack->push(transition);
	}
	m_menu_text.build(frame, m_camera, view);
	m_press_space_text.build(frame, m_camera, view);
}

void MenuState::onExit() {

}