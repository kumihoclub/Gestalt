#pragma once

#include "sp_common.h"
#include "sp_sprite.h"
#include "sp_frame.h"

class SPRenderer {
public:
	void init();
	void shutdown();
	void draw(SPFrame& frame);

private:
	struct SPVertex {
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 position = { 0.0f, 0.0f , 0.0f, 1.0f };
		glm::vec2 sprite_uv = { 0.0f, 0.0f };
	};

	std::vector<SPVertex> m_vertex;
	struct {
		u32 main_shader = 0;
		u32 vbo = 0;
		u32 vao = 0;
		u32 uni_texture = 0;
	} m_gl;

};