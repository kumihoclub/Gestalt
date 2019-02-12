#pragma once

#include "sp_common.h"
#include "sp_prop.h"

#include <vector>
#include <string>

struct SPLayer {
	std::string name = "";
	std::string file = "";
	u32 size = 0;
	u32 stride = 0;
	u32 depth = 0;
	std::vector<SPProp> tile_props;
};