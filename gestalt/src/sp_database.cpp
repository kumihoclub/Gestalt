
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include "std_filesystem.h"
#include "stb/stb_image.h"
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
}

void SPDatabase::init() {
	std::ifstream database_file;
	std::stringstream database_stream;
	database_file.open("data/salt.dat");
	database_stream << database_file.rdbuf();
	database_file.close();
	m_database_raw = database_stream.str();

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