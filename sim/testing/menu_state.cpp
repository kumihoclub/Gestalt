
#include "menu_state.h"
#include "test_state.h"

void MenuState::onEnter() {
	m_menu_text.set("\"Main Menu\"");
}

void MenuState::update(SPViewport& view, SPFrame& frame, BTTransitionStack* transition_stack) {
	if (m_space.pressed()) {
		TestState* test = new TestState();
		BTTransition transition;
		transition.type = BT_TRANSITION_TYPE_PUSH_PRESERVE;
		transition.state = test;
		transition_stack->push(transition);
	}
	m_menu_text.build(frame, m_camera, view);
}

void MenuState::onExit() {

}