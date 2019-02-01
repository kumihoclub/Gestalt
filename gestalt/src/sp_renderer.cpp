
#include "glad/glad.h"
#include "sp_gl_err.h"

#include "sp_renderer.h"

void SPRenderer::init() {

	glGenBuffers(1, &m_gl.vbo); spCheckGLError();
	glGenVertexArrays(1, &m_gl.vao); spCheckGLError();
	glBindVertexArray(m_gl.vao); spCheckGLError();
	glBindBuffer(GL_ARRAY_BUFFER, m_gl.vbo); spCheckGLError();
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(SPVertex) * (6 * 16384), nullptr, GL_DYNAMIC_DRAW);
	}
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(0)); spCheckGLError();
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float))); spCheckGLError();
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float))); spCheckGLError();
	glEnableVertexAttribArray(0); spCheckGLError();
	glEnableVertexAttribArray(1); spCheckGLError();
	glEnableVertexAttribArray(2); spCheckGLError();
	glBindVertexArray(0); spCheckGLError();

}

void SPRenderer::shutdown() {
	glDeleteProgram(m_gl.main_shader);
	glDeleteVertexArrays(1, &m_gl.vao);
	glDeleteBuffers(1, &m_gl.vbo);
}

void SPRenderer::draw(SPFrame& frame) {

	m_vertex.reserve(frame.renderables.size() * 6);
	m_vertex.resize(0);
	int x, y;
	SPRenderable* last = nullptr;
	for (auto& renderable : frame.renderables) {
		if (!last) {
			last = &renderable;
		}
		if (renderable.material.sprite.image_id != last->material.sprite.image_id) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, last->material.sprite.image_id);
			glUseProgram(last->material.shader->id());
			glBindVertexArray(m_gl.vao);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SPVertex) * m_vertex.size(), m_vertex.data());
			glDrawArrays(GL_TRIANGLES, 0, m_vertex.size());
			m_vertex.resize(0);
		}
		SPVertex vert[6];
		vert[0].position = renderable.mvp * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
		vert[1].position = renderable.mvp * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
		vert[2].position = renderable.mvp * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
		vert[3].position = renderable.mvp * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
		vert[4].position = renderable.mvp * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		vert[5].position = renderable.mvp * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
		vert[0].color = renderable.material.color;
		vert[1].color = renderable.material.color;
		vert[2].color = renderable.material.color;
		vert[3].color = renderable.material.color;
		vert[4].color = renderable.material.color;
		vert[5].color = renderable.material.color;
		// Shorthand for sanitys sake
		f32 u = renderable.material.sprite.uv.x;
		f32 v = renderable.material.sprite.uv.y;
		f32 w = renderable.material.sprite.size_norm.x;
		f32 h = renderable.material.sprite.size_norm.y;
		/*vert[0].sprite_uv = { u + w, v };
		vert[1].sprite_uv = { u + w, v + h };
		vert[2].sprite_uv = { u, v };
		vert[3].sprite_uv = { u + w, v + h };
		vert[4].sprite_uv = { u, v + h };
		vert[5].sprite_uv = { u, v };*/

		vert[0].sprite_uv = { u + w, v + h };
		vert[1].sprite_uv = { u + w, v };
		vert[2].sprite_uv = { u, v + h };

		vert[3].sprite_uv = { u + w, v };
		vert[4].sprite_uv = { u, v };
		vert[5].sprite_uv = { u, v + h };

		/*vert[0].sprite_uv = { u + w, 1.0f - v };
		vert[1].sprite_uv = { u + w, 1.0f - (v + h) };
		vert[2].sprite_uv = { u, 1.0f - v };
		vert[3].sprite_uv = { u + w, 1.0f - (v + h) };
		vert[4].sprite_uv = { u, 1.0f - (v + h) };
		vert[5].sprite_uv = { u, 1.0f - v };*/

		/*vert[0].sprite_uv = { u + w, 1.0f - (v + h) };
		vert[1].sprite_uv = { u + w, 1.0f - v };
		vert[2].sprite_uv = { u, 1.0f - (v + h) };

		vert[3].sprite_uv = { u + w, 1.0f - v };
		vert[4].sprite_uv = { u, 1.0f - v };
		vert[5].sprite_uv = { u, 1.0f - (v + h) };*/

		/*

		/ first triangle
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left
		// second triangle
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left


		// positions          // colors           // image_id coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
		*/
		m_vertex.push_back(vert[0]);
		m_vertex.push_back(vert[1]);
		m_vertex.push_back(vert[2]);
		m_vertex.push_back(vert[3]);
		m_vertex.push_back(vert[4]);
		m_vertex.push_back(vert[5]);
		last = &renderable;
	}

	if (m_vertex.size() > 0) {
		glActiveTexture(GL_TEXTURE0);
		glUseProgram(last->material.shader->id()); spCheckGLError();
		glBindTexture(GL_TEXTURE_2D, last->material.sprite.image_id); spCheckGLError();
		glBindVertexArray(m_gl.vao); spCheckGLError();
		glBufferData(GL_ARRAY_BUFFER, sizeof(SPVertex) * m_vertex.size(), m_vertex.data(), GL_DYNAMIC_DRAW); spCheckGLError();
		glDrawArrays(GL_TRIANGLES, 0, m_vertex.size()); spCheckGLError();
		m_vertex.resize(0);
	}
}