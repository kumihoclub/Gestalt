#pragma once

#include "sp_common.h"

#include <stack>

class BTState;

enum BTTransitionType {
	BT_TRANSITION_TYPE_PUSH_PRESERVE, // Push the included state to the top of the state stack preserving the previous
	BT_TRANSITION_TYPE_PUSH_RELEASE, // Push the included state to the top of the state stack releasing the previous
	BT_TRANSITION_TYPE_POP  // Pops the curent state off the state stack, releasing it in the process.
};

struct BTTransition {
	BTState* state = nullptr;
	BTTransitionType type = BT_TRANSITION_TYPE_PUSH_PRESERVE;
};

using BTTransitionStack = std::stack<BTTransition>;