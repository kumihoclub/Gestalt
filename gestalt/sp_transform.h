#pragma once

#include "sp_common.h"

#include "glm/glm.hpp"

#define SP_ORIGIN_CENTER glm::vec2(0.0f, 0.0f);
#define SP_ORIGIN_TOP_LEFT glm::vec2(-1.0f, -1.0f);
#define SP_ORIGIN_TOP_RIGHT glm::vec2(1.0f, -1.0f);
#define SP_ORIGIN_BOTTOM_LEFT glm::vec2(-1.0f, 1.0f);
#define SP_ORIGIN_BOTTOM_RIGHT glm::vec2(1.0f, 1.0f);

enum SPAnchor {
	SP_ANCHOR_WORLD,
	SP_ANCHOR_VIEWPORT
};

struct SPTransform {
	glm::vec2 pos = { 0.0f, 0.0f };
	glm::vec2 scale = { 1.0f, 1.0f };
	glm::vec2 origin = SP_ORIGIN_CENTER;
	SPAnchor anchor = SP_ANCHOR_WORLD;
	f32 rot = 0;
	u32 layer = 0;
};