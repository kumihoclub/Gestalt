#pragma once

#include "sp_prop.h"

// Prob inefficient as hell but since there wont ever be more than maybe 8-12 battle actors active at a time, I doubt the cache misses will matter

struct BattleActor {
	SPProp m_actor_prop;

};