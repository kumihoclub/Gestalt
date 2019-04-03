

#include "test_sim.h"
#include "menu_state.h"

#include <stack>

namespace {
	SPStateStack m_state_stack;
	SPTransitionStack m_transition_stack;

}

void TestSim::init() {
	// TEST:
	MenuState* test = new MenuState();
	m_state_stack.push(test);
	test->onEnter();
	//END TEST:
}

void TestSim::update(SPFrame& frame) {
	if (m_state_stack.size() > 0) {
		m_state_stack.top()->update(frame, &m_transition_stack);
		if (m_transition_stack.size() > 0) {
			SPTransition transition = m_transition_stack.top();
			if (transition.type == SP_TRANSITION_TYPE_PUSH_RELEASE) {
				m_state_stack.top()->onExit();
				delete m_state_stack.top();
				m_state_stack.pop();
			}
			if (transition.type == SP_TRANSITION_TYPE_PUSH_PRESERVE || transition.type == SP_TRANSITION_TYPE_PUSH_RELEASE) {
				m_state_stack.push(transition.state);
				m_state_stack.top()->onEnter();
			}
			if (transition.type == SP_TRANSITION_TYPE_POP) {
				m_state_stack.top()->onExit();
				m_state_stack.pop();
			}
			//TODO: Handle transition effects
			m_transition_stack.pop();
		}
	}
}

void TestSim::shutdown() {

}