
#include "sp_font_cache.h"
#include "sp_gl_err.h"
#include "sp_glyph.h"

#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "std_filesystem.h"
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_rect_pack.h"
#include "stb/stb_truetype.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <fstream>
#include <iostream>

namespace {

	struct PackedFont {
		u32 image;
		std::unordered_map<char, SPGlyph> glyphs;
	};

	b32 flip = false;
	u8* bitmap;
	std::vector<char> font_buffer;
	stbtt_fontinfo font_info;
	stbtt_packedchar* packed_chars;
	PackedFont font;

}

void SPFontCache::init(b32 flip_textures) {
	
	flip = flip_textures;

	std_filesystem::path image_path = "data/font/Mukta-Regular.ttf";

	std::ifstream font_file(image_path, std::ios::binary | std::ios::ate);
	std::streamsize size = font_file.tellg();
	font_file.seekg(0, std::ios::beg);

	font_buffer.resize(size);
	if (font_file.read(font_buffer.data(), size)) {

		stbtt_InitFont(&font_info, (unsigned char*)font_buffer.data(), 0);

		bitmap = new u8[1024 * 1024];
		const i32 glyph_count = 128;
		stbtt_pack_context pack_context;
		int res = stbtt_PackBegin(&pack_context, bitmap, 1024, 1024, 0, 1, nullptr);
		if (!res) {
			std::cout << "Failed to initialize font packing." << std::endl;
		}

		packed_chars = new stbtt_packedchar[128];
		res = stbtt_PackFontRange(&pack_context, (unsigned char*)font_buffer.data(), 0, 96, 0, glyph_count, packed_chars);
		if (!res) {
			std::cout << "Failed to perform font packing." << std::endl;
		}

		stbtt_PackEnd(&pack_context);

		if (flip) {
			int w = 1024, h = 1024;
			int channels = 1;
			int row, col, z;
			//stbi_uc *image = (stbi_uc *)result;

			// @OPTIMIZE: use a bigger temp buffer and memcpy multiple pixels at once
			for (row = 0; row < (h >> 1); row++) {
				for (col = 0; col < w; col++) {
					for (z = 0; z < channels; z++) {
						unsigned char temp = bitmap[(row * w + col) * channels + z];
						bitmap[(row * w + col) * channels + z] = bitmap[((h - row - 1) * w + col) * channels + z];
						bitmap[((h - row - 1) * w + col) * channels + z] = temp;
					}
				}
			}
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); spCheckGLError();// Disable byte-alignment restriction

		glGenTextures(1, &font.image); spCheckGLError();
		glBindTexture(GL_TEXTURE_2D, font.image); spCheckGLError();
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			1024,
			1024,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bitmap
		); spCheckGLError();
		// Set image_id options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); spCheckGLError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); spCheckGLError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); spCheckGLError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); spCheckGLError();
		// Now store character for later use
		

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); spCheckGLError();

		for (i32 i = 0; i < glyph_count; i++) {
			SPGlyph new_glyph;
			new_glyph.val = i;
			new_glyph.sprite.uv = { (f32)packed_chars[i].x0 / (f32)1024, (f32)packed_chars[i].y0 / (f32)1024 };
			new_glyph.sprite.size_exact = { packed_chars[i].x1 - packed_chars[i].x0, packed_chars[i].y1 - packed_chars[i].y0 };
			new_glyph.sprite.size_norm = { new_glyph.sprite.size_exact.x / (f32)1024, new_glyph.sprite.size_exact.y / (f32)1024 };
			new_glyph.sprite.image_id = font.image;
			new_glyph.offset = { 
				(packed_chars[i].xoff + (new_glyph.sprite.size_exact.x / 2)) / SP_UNIT_PIXELS,
				(packed_chars[i].yoff + (new_glyph.sprite.size_exact.y / 2)) / SP_UNIT_PIXELS,
			};
			new_glyph.advance = (f32)packed_chars[i].xadvance / SP_UNIT_PIXELS;
			font.glyphs[(char)i] = new_glyph;
		}

	}
	else {
		std::cout << "Failed to load font." << std::endl;

	}
	font_file.close();

	delete[] bitmap;
	delete[] packed_chars;

}

void SPFontCache::shutdown() {
	glDeleteTextures(1, &font.image);
}

SPGlyph SPFontCache::fetchGlyph(char glyph) {
	return font.glyphs[glyph];
}

f32 SPFontCache::kernOffset(SPGlyph* cur, SPGlyph* next) {
	f32 res = stbtt_GetGlyphKernAdvance(&font_info, cur->val, next->val);
	return res;
}