
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION

#include "glad/glad.h"
#include "std_filesystem.h"
#include "stb/stb_image.h"
#include "sp_gl_err.h"

#include "sp_sprite_cache.h"
#include "sp_image.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace {

	std::unordered_map<std::string, SPSprite> registry;
	std::vector<SPImage> images;
	SPSprite debug_sprite;

}

//SPSprite::SPSprite() {}

/*SPSprite::SPSprite(std::string name) {
	*this = SPSpriteCache::fetchSprite(name);
}*/

void SPSpriteCache::init() {
	stbi_set_flip_vertically_on_load(true);
	for (auto& dir : std_filesystem::recursive_directory_iterator("data/registry/sprite/")) { // God I love std::filesystem
		if (dir.path().extension().string() == ".json") {

			// Open file
			std::ifstream atlas_file;
			std::stringstream atlas_stream;
			atlas_file.open(dir);
			atlas_stream << atlas_file.rdbuf();
			atlas_file.close();
			json atlas_json = json::parse(atlas_stream.str());

			// load and generate the image_id(s)

			// Single atlas
			parseAtlasJSON(atlas_json);

		}
	}

	u32 debug_texture = generateDebugTexture();
	SPSprite debug_sprite;
	debug_sprite.image_id = debug_texture;
	debug_sprite.size_exact = { 32.0f, 32.0f };
	debug_sprite.size_norm = { 32.0f / SP_UNIT_PIXELS, 32.0f / SP_UNIT_PIXELS };
	debug_sprite = debug_sprite;
}

void SPSpriteCache::shutdown() {
	for (auto& image : images) {
		glDeleteTextures(1, &image.id);
	}
	registry.clear();
}
 
SPSprite SPSpriteCache::fetchSprite(const std::string name) {
	if (name != "") {
		if (registry.find(name) != registry.end()) {
			SPSprite sprite = registry[name];
			return sprite;
		}
		else {
			std::cout << "Sprite \"" + name + "\" not found. Substituting debug sprite" << std::endl;
		}
	}
	return debug_sprite;
}

void SPSpriteCache::parseAtlasJSON(json& atlas_json) {

	if (atlas_json.find("frames") != atlas_json.end() && atlas_json.find("meta") != atlas_json.end()) {

		json meta = atlas_json["meta"];
		std::string image_name = meta["image"];
		std_filesystem::path image_path = "data/registry/sprite";
		image_path /= image_name;
		SPImage new_image;
		if (std_filesystem::exists(image_path)) {
			// Load image
			unsigned char *data = stbi_load(image_path.u8string().c_str(), &new_image.x, &new_image.y, &new_image.num_chans, 0);
			if (data) { 
				glGenTextures(1, &new_image.id); spCheckGLError();
				glBindTexture(GL_TEXTURE_2D, new_image.id); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); spCheckGLError();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); spCheckGLError();
				if (new_image.num_chans == 4) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, new_image.x, new_image.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); spCheckGLError();
				}
				else if (new_image.num_chans == 3) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, new_image.x, new_image.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data); spCheckGLError();
				}
				glGenerateMipmap(GL_TEXTURE_2D);
				stbi_image_free(data);
				images.push_back(new_image);
			}
			else {
				std::cout << "Image file \"" + image_name + "\" failed to load. Substituting debug sprite." << std::endl;
			}
		}
		else {
			std::cout << "Image file \"" + image_name + "\" not found. Substituting debug sprite." << std::endl;
		}
		std::vector<json> frames = atlas_json["frames"];
		for (auto& frame : frames) {
			std::string sprite_name = frame["filename"];
			if (new_image.id != 0) {
				SPSprite new_sprite;
				json frame_params = frame["frame"];
				new_sprite.uv.x = (frame_params["x"] / new_image.x);
				new_sprite.uv.y = (frame_params["y"] / new_image.y);
				new_sprite.size_exact.x = frame_params["w"];
				new_sprite.size_exact.y = frame_params["h"];
				new_sprite.size_norm.x = new_sprite.size_exact.x / (f32)new_image.x;
				new_sprite.size_norm.y = new_sprite.size_exact.x / (f32)new_image.y;
				new_sprite.image_id = new_image.id;
				registry[sprite_name] = new_sprite;
			}
			else {
				registry[sprite_name] = debug_sprite;
			}
		}
	}
}

u32 SPSpriteCache::generateDebugTexture() {
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
	u32 debug_texture = 0;
	glGenTextures(1, &debug_texture); spCheckGLError(); 
	glBindTexture(GL_TEXTURE_2D, debug_texture); spCheckGLError();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); spCheckGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); spCheckGLError();
	glBindTexture(GL_TEXTURE_2D, 0); spCheckGLError();
	return debug_texture;
}
