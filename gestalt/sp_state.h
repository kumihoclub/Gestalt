#pragma once

#include "sp_common.h"
#include "sp_viewport.h"
#include "sp_frame.h"

#include "sp_transition.h"

#include <stack>

class SPState {
public:
	virtual void onEnter() = 0;
	virtual void update(SPViewport& view, SPFrame& frame, SPTransitionStack* transition_stack) = 0;
	virtual void onExit() = 0;

};


using SPStateStack = std::stack<SPState*>;