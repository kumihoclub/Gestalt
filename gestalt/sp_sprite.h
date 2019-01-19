#pragma once

#include "sp_common.h"

#include "glm/glm.hpp"

#include <string>

struct SPSprite {
	u32 image_id = 0;
	glm::vec2 uv = { 0.0f, 0.0f };
	glm::vec2 size_norm = { 1.0f, 1.0f };
	glm::vec2 size_exact = { 1.0f, 1.0f };
};