#pragma once

#include "sp_common.h"
#include "sp_material.h"

#include "glm/glm.hpp"

struct SPRenderable {
	glm::mat4 mvp = glm::mat4(1.0f);
	SPMaterial material;
	i32 layer = 0;
};