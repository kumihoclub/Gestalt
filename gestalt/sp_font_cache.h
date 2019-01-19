#pragma once

#include "sp_common.h"
#include "sp_sprite.h"
#include "sp_prop.h"
#include "sp_glyph.h"

#include "nlohmann/json.hpp"
#include "glm/glm.hpp"
#include "stb/stb_truetype.h"

#include <string>
#include <vector>
#include <unordered_map>

using json = nlohmann::json;

class SPFontCache {
public:
	void init();
	void shutdown();
	static SPGlyph fetchGlyph(char glyph);
	static f32 kernOffset(SPGlyph* cur, SPGlyph* next);

private:
	void compileImage();

};