#pragma once

#include "sp_common.h"
#include "sp_material.h"
#include "sp_collider.h"
#include "sp_transform.h"
#include "sp_camera.h"
#include "sp_viewport.h"
#include "sp_renderable.h"

#include "glm/glm.hpp"

struct SPProp {
	SPTransform transform;
	optional<SPMaterial> material;
	optional<SPCollider> collider;
	SPRenderable renderable(SPCamera& camera, SPViewport& viewport);
};