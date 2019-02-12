
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include "std_filesystem.h"
#include "stb/stb_image.h"
//#include "lua/lua.h"
//#include "sol2/sol_forward.hpp"
#include "sol2/sol.hpp"
#include "sp_gl_err.h"

#include "sp_database.h"
#include "sp_texture.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Most data is going to be static via anon namespace, SPDatabase type is more to limit global access to sensitive procs (init/shutdown/whataver else gets added later on)

namespace {

	std::string m_database_raw;
	std::unordered_map<std::string, SPSprite> m_sprite_cache;
	std::unordered_map<std::string, SPTexture> m_texture_cache;
	SPSprite m_debug_sprite;
	sol::state m_lua_state;

}

void SPDatabase::init() {
	m_lua_state.open_libraries(sol::lib::base, sol::lib::package);
	std::ifstream database_file;
	std::stringstream database_stream;
	database_file.open("data/salt.dat");
	database_stream << database_file.rdbuf();
	database_file.close();
	m_database_raw = database_stream.str();

	setupLua();
	generateDebugSprite();
	loadImages();
	loadSprites();
}

void SPDatabase::shutdown() {
	for (auto& cached : m_texture_cache) {
		glDeleteTextures(1, &cached.second.id);
	}
	m_texture_cache.clear();
	m_sprite_cache.clear();
}

SPSprite SPDatabase::fetchSprite(const std::string name) {
	if (name != "") {
		if (m_sprite_cache.find(name) != m_sprite_cache.end()) {
			SPSprite sprite = m_sprite_cache[name];
			return sprite;
		}
		else {
			std::cout << "Sprite \"" + name + "\" not found. Substituting debug sprite" << std::endl;
		}
	}
	return m_debug_sprite;
}

void SPDatabase::setupLua() {
	//m_lua_state.new_usertype<SPProp>("prop");
	m_lua_state.new_usertype<glm::vec2>("vec2",
		sol::constructors< glm::vec2(), glm::vec2(double, double) >(),
		"x", &glm::vec2::x,
		"y", &glm::vec2::y,
		sol::meta_function::addition, [](const glm::vec2& left, const glm::vec2& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::vec2& left, const glm::vec2& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::vec2& left, const glm::vec2& right) { return left * right; },
		sol::meta_function::division, [](const glm::vec2& left, const glm::vec2& right) { return left / right; }
	);
	m_lua_state.new_usertype<glm::vec3>("vec3",
		sol::constructors< glm::vec3(), glm::vec3(double, double, double) >(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z,
		sol::meta_function::addition, [](const glm::vec3& left, const glm::vec3& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::vec3& left, const glm::vec3& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::vec3& left, const glm::vec3& right) { return left * right; },
		sol::meta_function::division, [](const glm::vec3& left, const glm::vec3& right) { return left / right; }
	);
	m_lua_state.new_usertype<glm::vec4>("vec4",
		sol::constructors< glm::vec4(), glm::vec4(double, double, double, double) >(),
		"x", &glm::vec4::x,
		"y", &glm::vec4::y,
		"z", &glm::vec4::z,
		"w", &glm::vec4::w,
		sol::meta_function::addition, [](const glm::vec4& left, const glm::vec4& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::vec4& left, const glm::vec4& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::vec4& left, const glm::vec4& right) { return left * right; },
		sol::meta_function::division, [](const glm::vec4& left, const glm::vec4& right) { return left / right; }
	);

	/*m_lua_state.new_usertype<glm::uvec2>("Uvec2",
		sol::constructors< glm::uvec2(), glm::uvec2(double, double) >(),
		"x", &glm::uvec2::x,
		"y", &glm::uvec2::y,
		sol::meta_function::addition, [](const glm::uvec2& left, const glm::uvec2& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::uvec2& left, const glm::uvec2& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::uvec2& left, const glm::uvec2& right) { return left * right; },
		sol::meta_function::division, [](const glm::uvec2& left, const glm::uvec2& right) { return left / right; }
	);
	m_lua_state.new_usertype<glm::uvec3>("Uvec3",
		sol::constructors< glm::uvec3(), glm::uvec3(double, double, double) >(),
		"x", &glm::uvec3::x,
		"y", &glm::uvec3::y,
		"z", &glm::uvec3::z,
		sol::meta_function::addition, [](const glm::uvec3& left, const glm::uvec3& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::uvec3& left, const glm::uvec3& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::uvec3& left, const glm::uvec3& right) { return left * right; },
		sol::meta_function::division, [](const glm::uvec3& left, const glm::uvec3& right) { return left / right; }
	);
	m_lua_state.new_usertype<glm::uvec4>("Uvec4",
		sol::constructors< glm::uvec4(), glm::uvec4(double, double, double, double) >(),
		"x", &glm::uvec4::x,
		"y", &glm::uvec4::y,
		"z", &glm::uvec4::z,
		"w", &glm::uvec4::w,
		sol::meta_function::addition, [](const glm::uvec4& left, const glm::uvec4& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::uvec4& left, const glm::uvec4& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::uvec4& left, const glm::uvec4& right) { return left * right; },
		sol::meta_function::division, [](const glm::uvec4& left, const glm::uvec4& right) { return left / right; }
	);

	m_lua_state.new_usertype<glm::ivec2>("Ivec2",
		sol::constructors< glm::ivec2(), glm::ivec2(double, double) >(),
		"x", &glm::ivec2::x,
		"y", &glm::ivec2::y,
		sol::meta_function::addition, [](const glm::ivec2& left, const glm::ivec2& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::ivec2& left, const glm::ivec2& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::ivec2& left, const glm::ivec2& right) { return left * right; },
		sol::meta_function::division, [](const glm::ivec2& left, const glm::ivec2& right) { return left / right; }
	);
	m_lua_state.new_usertype<glm::ivec3>("Ivec3",
		sol::constructors< glm::ivec3(), glm::ivec3(double, double, double) >(),
		"x", &glm::ivec3::x,
		"y", &glm::ivec3::y,
		"z", &glm::ivec3::z,
		sol::meta_function::addition, [](const glm::ivec3& left, const glm::ivec3& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::ivec3& left, const glm::ivec3& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::ivec3& left, const glm::ivec3& right) { return left * right; },
		sol::meta_function::division, [](const glm::ivec3& left, const glm::ivec3& right) { return left / right; }
	);
	m_lua_state.new_usertype<glm::ivec4>("Ivec4",
		sol::constructors< glm::ivec4(), glm::ivec4(double, double, double, double) >(),
		"x", &glm::ivec4::x,
		"y", &glm::ivec4::y,
		"z", &glm::ivec4::z,
		"w", &glm::ivec4::w,
		sol::meta_function::addition, [](const glm::ivec4& left, const glm::ivec4& right) { return left + right; },
		sol::meta_function::subtraction, [](const glm::ivec4& left, const glm::ivec4& right) { return left - right; },
		sol::meta_function::multiplication, [](const glm::ivec4& left, const glm::ivec4& right) { return left * right; },
		sol::meta_function::division, [](const glm::ivec4& left, const glm::ivec4& right) { return left / right; }
	);*/
}

void SPDatabase::loadImages() {
	stbi_set_flip_vertically_on_load(true);
	for (auto& dir : std_filesystem::recursive_directory_iterator("data/texture/")) { // God I love std::filesystem
		if (dir.path().extension().string() == ".png") {

			SPTexture new_texture;
			unsigned char *data = stbi_load(dir.path().u8string().c_str(), &new_texture.x, &new_texture.y, &new_texture.num_chans, 0);
			if (data) {
				glGenTextures(1, &new_texture.id); spCheckGLError();
				glBindTexture(GL_TEXTURE_2D, new_texture.id); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); spCheckGLError();
				if (new_texture.num_chans == 4) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, new_texture.x, new_texture.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); spCheckGLError();
				}
				else if (new_texture.num_chans == 3) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, new_texture.x, new_texture.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data); spCheckGLError();
				}
				glGenerateMipmap(GL_TEXTURE_2D);
				stbi_image_free(data);
				// Remove the "data" suffix from the directory
				std::string parsed_path = dir.path().u8string();
				std::string data_rem = "data\\";
				std::string::size_type i = parsed_path.find(data_rem);
				if (i != std::string::npos)
					parsed_path.erase(i, data_rem.length());
				m_texture_cache[parsed_path] = new_texture;
			}

		}
	}

}
void SPDatabase::loadSprites() {
	json database_raw = json::parse(m_database_raw);
	std::vector<json> sheets = database_raw["sheets"];
	for (auto& sheet : sheets) {
		if (sheet["name"] == "sprite") {
			std::vector<json> sprites = sheet["lines"];
			for (auto& sprite : sprites) {
				SPSprite new_sprite;
				std::string file = sprite["sprite"]["file"];
				// Convert to std::filesystem path to ensure the keys match in the caches
				std_filesystem::path file_path = file;
				SPTexture texture = m_texture_cache[file_path.u8string()];
				std::string sprite_name = sprite["name"];
				u32 size = sprite["sprite"]["size"];
				new_sprite.size_exact = { size, size };
				new_sprite.size_norm = { (f32)size / (f32)texture.x, (f32)size / (f32)texture.y };
				new_sprite.uv = { (f32)(sprite["sprite"]["x"] * size) / (f32)texture.x, (f32)(sprite["sprite"]["y"] * size) / (f32)texture.y };
				new_sprite.texture_id = texture.id;
				m_sprite_cache[sprite_name] = new_sprite;
			}
		}
	}
}

void SPDatabase::generateDebugSprite() {
	u8 image_data[32][32][3]; // Texture image data
	i32 value;
	for (int row = 0; row < 32; row++) {
		for (int col = 0; col < 32; col++) {
			// Each cell is 8x8, value is 0 or 255 (black or white)
			value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
			image_data[row][col][0] = (u8)value;
			image_data[row][col][1] = (u8)value;
			image_data[row][col][2] = (u8)value;
		}
	}
	glGenTextures(1, &m_debug_sprite.texture_id); spCheckGLError();
	glBindTexture(GL_TEXTURE_2D, m_debug_sprite.texture_id); spCheckGLError();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); spCheckGLError();
	glBindTexture(GL_TEXTURE_2D, 0); spCheckGLError();
	m_debug_sprite.size_exact = { 32, 32 };
	m_debug_sprite.size_norm = { 1.0f, 1.0f };
	m_debug_sprite.uv = { 1.0f, 1.0f };
}