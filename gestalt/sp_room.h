#pragma once

#include "sp_common.h"
#include "sp_layer.h"

#include <vector>

class SPRoom {
public:

private:
	u32 m_actor_depth;
	std::vector<SPLayer> m_layers;
};