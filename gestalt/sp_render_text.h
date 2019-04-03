#pragma once

#include "sp_common.h"
#include "sp_prop.h"
#include "sp_frame.h"
#include "sp_glyph.h"

#include "stb/stb_truetype.h"

#include <vector>
#include <string>

class SPRenderText {
public:
	SPRenderText();
	SPRenderText(std::string text);
	void build(SPFrame& frame, SPCamera& camera);
	void set(std::string text);
	SPTransform transform;
	glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
private:
	std::string m_text;
	std::vector<SPGlyph> m_glyphs;
	f32 m_full_x = 0.0f;
	f32 m_largest_y = 0.0f;
};