#pragma once

#include "sp_common.h"

#include "glm/glm.hpp"

enum SPFixtureType {
	SP_NULL_FIXTURE,
	SP_BOX_FIXTURE,
	SP_ELLIPSE_FIXTURE
};

struct SPCollider {
	SPFixtureType fixture_type = SP_NULL_FIXTURE;
	union {
		struct {
			glm::vec2 offset;
			glm::vec2 size;
			f32 rot;
		} box;
		struct SPCircleFixture {
			glm::vec2 offset;
			f32 radius;
		} ellipse;
	} fixture;
};