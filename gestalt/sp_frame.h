#pragma once

#include "sp_common.h"
#include "sp_sprite.h"
#include "sp_renderable.h"

#include "glm/glm.hpp"

#include <chrono>
#include <vector>

// SPFrame source is located in SPWindow

using high_res_clock = std::chrono::high_resolution_clock;
using timestamp = std::chrono::time_point<std::chrono::high_resolution_clock>;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

struct SPFrame {
	void reset();
	void sort();
	void set_lock(u32 fps);
	b32 ready();
	std::vector<SPRenderable> renderables;
private:
	milliseconds m_target_time;
	nanoseconds m_current_time;
	timestamp m_timestamp;
};
