#include "sp_shader_cache.h"

#include <unordered_map>

namespace {

	std::unordered_map<std::string, SPShader> m_shaders;

}

void SPShaderCache::init() {

	// Generate sprite default shader

	std::string vert_src =
		"#version 400 core\n"
		"layout(location = 0) in vec4 v_color;"
		"layout(location = 1) in vec4 v_position;"
		"layout(location = 2) in vec2 v_uv;"
		"out vec4 f_color;"
		"out vec2 f_uv;"
		"void main()"
		"{"
		"f_color = v_color;"
		"f_uv = vec2(v_uv.x, 1.0 - v_uv.y);"
		"gl_Position = v_position;"
		//"gl_Position = vec4(v_position, 0.0, 1.0);"
		"}";

	std::string default_sprite_shader_frag_src =
		"#version 400 core\n"
		"in vec4 f_color;"
		"in vec2 f_uv;"
		"out vec4 final_color;"
		"uniform sampler2D u_texture;"
		"void main()"
		"{"
		"vec4 tex_color = texture(u_texture, f_uv) * f_color;"
		"if (tex_color.a < 0.1) {"
		"discard;}"
		"final_color = tex_color;"
		"}";

	SPShader default_sprite_shader(vert_src, default_sprite_shader_frag_src);

	u32 u_texture = default_sprite_shader.getUniformLocation("u_texture");
	default_sprite_shader.setUniformValue(u_texture, 0);

	m_shaders["sprite_default"] = default_sprite_shader;

	// Generate font default shader

	std::string default_font_shader_frag_src =
		"#version 400 core\n"
		"in vec4 f_color;"
		"in vec2 f_uv;"
		"out vec4 final_color;"
		"uniform sampler2D u_texture;"
		"void main()"
		"{"
		"vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, f_uv).r);"
		"final_color = f_color * sampled;"
		"}";

	SPShader default_font_shader(vert_src, default_font_shader_frag_src);

	u_texture = default_font_shader.getUniformLocation("u_texture");
	default_font_shader.setUniformValue(u_texture, 0);

	m_shaders["font_default"] = default_font_shader;

}

void SPShaderCache::shutdown() {
	std::unordered_map<std::string, SPShader>::iterator it = m_shaders.begin();
	// Iterate over the map using Iterator till end.
	while (it != m_shaders.end()) {
		glDeleteProgram(it->second.m_id);
		it++;
	}
	m_shaders.clear();
}

void SPShaderCache::compileShader(std::string& vert_src, std::string frag_src, std::string& name) {
	SPShader new_shader(vert_src, frag_src);
	m_shaders[name] = new_shader;
}

SPShader* SPShaderCache::fetchShader(const std::string name) {
	if (m_shaders.find(name) != m_shaders.end()) {
		return &m_shaders[name];
	}
	return nullptr;
}