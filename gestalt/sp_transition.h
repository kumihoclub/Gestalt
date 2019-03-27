#pragma once

#include "sp_common.h"

#include <stack>

class SPState;

enum SPTransitionType {
	SP_TRANSITION_TYPE_PUSH_PRESERVE, // Push the included state to the top of the state stack preserving the previous
	SP_TRANSITION_TYPE_PUSH_RELEASE, // Push the included state to the top of the state stack releasing the previous
	SP_TRANSITION_TYPE_POP  // Pops the curent state off the state stack, releasing it in the process.
};

struct SPTransition {
	SPState* state = nullptr;
	SPTransitionType type = SP_TRANSITION_TYPE_PUSH_PRESERVE;
};

using SPTransitionStack = std::stack<SPTransition>;