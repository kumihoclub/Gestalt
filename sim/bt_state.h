#pragma once

#include "sp_common.h"
#include "sp_viewport.h"
#include "sp_frame.h"

#include "bt_transition.h"

#include <stack>

class BTState {
public:
	virtual void onEnter() = 0;
	virtual void update(SPViewport& view, SPFrame& frame, BTTransitionStack* transition_stack) = 0;
	virtual void onExit() = 0;

};


using BTStateStack = std::stack<BTState*>;