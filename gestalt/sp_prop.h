#pragma once

#include "sp_common.h"
#include "sp_material.h"
#include "sp_collider.h"
#include "sp_transform.h"
#include "sp_camera.h"
#include "sp_renderable.h"
#include "sp_option.h"

#include "glm/glm.hpp"

struct SPProp {
	SPTransform transform;
	option<SPMaterial> material;
	option<SPCollider> collider;
	SPRenderable renderable(SPCamera& camera);
};