#pragma once

#include "sp_common.h"

#include "glm/glm.hpp"

struct SPViewport {
	glm::vec2 size = { 960.0f, 540.0f };
	f32 scale = 1.0;
};