
#include "bt_sim.h"
#include "bt_state.h"
#include "bt_transition.h"

//TEST
#include "testing/menu_state.h"
//END TEST

#include <stack>

namespace {
	BTStateStack m_state_stack;
	BTTransitionStack m_transition_stack;

}

void BTSim::init() {
	// TEST:
	MenuState* test = new MenuState();
	m_state_stack.push(test);
	test->onEnter();
	//END TEST:
}

void BTSim::update(SPViewport& view, SPFrame& frame) {
	if (m_state_stack.size() > 0) {
		m_state_stack.top()->update(view, frame, &m_transition_stack);
		if (m_transition_stack.size() > 0) {
			BTTransition transition = m_transition_stack.top();
			if (transition.type == BT_TRANSITION_TYPE_PUSH_RELEASE) {
				m_state_stack.top()->onExit();
				delete m_state_stack.top();
				m_state_stack.pop();
			}
			if (transition.type == BT_TRANSITION_TYPE_PUSH_PRESERVE || transition.type == BT_TRANSITION_TYPE_PUSH_RELEASE) {
				m_state_stack.push(transition.state);
				m_state_stack.top()->onEnter();
			}
			if (transition.type == BT_TRANSITION_TYPE_POP) {
				m_state_stack.top()->onExit();
				m_state_stack.pop();
			}
			//TODO: Handle transition effects
			m_transition_stack.pop();
		}
	}
}

void BTSim::shutdown() {

}