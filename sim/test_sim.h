#pragma once

#include "sp_common.h"
#include "sp_sim.h"
#include "sp_frame.h"
#include "sp_viewport.h"

class TestSim : public SPSim {
public:
	void init();
	void update(SPViewport& view, SPFrame& frame);
	void shutdown();
};