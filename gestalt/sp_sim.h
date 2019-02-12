#pragma once

#include "sp_common.h"

#include "sp_frame.h"
#include "sp_viewport.h"

class SPSim {
public:
	virtual ~SPSim() = 0;
	virtual void init() = 0;
	virtual void update(SPViewport& view, SPFrame& frame) = 0;
	virtual void shutdown() = 0;
private:

};