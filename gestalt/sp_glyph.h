#pragma once

#include "sp_common.h"
#include "sp_sprite.h"

#include "stb/stb_truetype.h"
#include "glm/glm.hpp"

struct SPGlyph {
	int val = 0;
	SPSprite sprite;
	glm::vec2 offset = { 0.0f, 0.0f };
	f32 advance = 0.0f;
};