#pragma once

#include "sp_common.h"
#include "sp_sim.h"
#include "sp_frame.h"

class TestSim : public SPSim {
public:
	void init();
	void update(SPFrame& frame);
	void shutdown();
};