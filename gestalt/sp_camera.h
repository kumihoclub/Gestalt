#pragma once

#include "sp_common.h"

#include "glm/glm.hpp"

struct SPCamera {
	glm::vec2 pos = { 0.0f, 0.0f };
	f32 scale = 1.0f;
};