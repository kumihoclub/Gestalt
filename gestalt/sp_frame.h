#pragma once

#include "sp_common.h"
#include "sp_sprite.h"
#include "sp_renderable.h"
#include "sp_alarm.h"

#include "glm/glm.hpp"

#include <vector>

struct SPFrame {
	void reset();
	void sort();
	void set_lock(u32 fps);
	b32 ready();
	std::vector<SPRenderable> renderables;
private:
	SPAlarm m_frame_alarm;
};
