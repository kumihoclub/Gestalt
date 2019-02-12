#pragma once

#include "sp_common.h"
#include "bt_transition.h"

#include <stack>

class SPStateHandler {
public:
	void pushTransition(BTTransition transition);
	void update();

private:
	std::stack<SPState*> m_stack_stack;
	std::stack<BTTransition> m_transition_stack;
};