
#include "sp_render_text.h"

#include "sp_font_cache.h"
#include "sp_shader_cache.h"
#include "sp_window.h"

SPRenderText::SPRenderText() {}

SPRenderText::SPRenderText(std::string text) {
	set(text);

}

void SPRenderText::build(SPFrame& frame, SPCamera& camera) {

	float xpos = 0.0f;
	float ypos = 0.0f;

	for (int i = 0; i < m_glyphs.size(); i++) {

		SPGlyph* glyph = &m_glyphs[i];

		SPProp new_prop;

		SPMaterial new_mat;
		new_mat.sprite = glyph->sprite;
		new_mat.shader = SPShaderCache::fetchShader("font_default");
		new_prop.material = new_mat;

		new_prop.transform.anchor = transform.anchor;

		if (transform.anchor == SP_ANCHOR_WORLD) {
			new_prop.transform.pos.x = (transform.pos.x - ((m_full_x / 2) * transform.scale.x)); // Start from "center" of full x length
			new_prop.transform.pos.x += (xpos + glyph->offset.x * transform.scale.x); // Calc glyph + xpos stride offset
			new_prop.transform.pos.x += (-((m_full_x / 2) * transform.origin.x)); // Apply origin offset

			new_prop.transform.pos.y = transform.pos.y + (glyph->offset.y * transform.scale.y); // Start from "center" of the tallest glpyh in the text
			new_prop.transform.pos.y += (((m_largest_y / 2) * transform.origin.y) / SP_UNIT_PIXELS); // Offset from origin

		}
		else if (transform.anchor == SP_ANCHOR_VIEWPORT) {

			// IT WORKS!

			/*
			This is kinda backwards. The viewport branch in the prop type requires the position to be in normalized view
			coordinates. Here we are calculating the non-normalized view units, converting them to normalized, and then
			converting them back to non-normalized units in the prop type. This may seem strange but the prop type is ment to
			represent any type of "concept" in the game and not just this text.
			*/

			glm::vec2 viewport_norm;
			viewport_norm.x = (((f32)SPWindow::getWidth() / 2) / SP_UNIT_PIXELS);
			viewport_norm.y = (((f32)SPWindow::getHeight() / 2) / SP_UNIT_PIXELS);
			viewport_norm.x *= transform.pos.x;
			viewport_norm.y *= -transform.pos.y;

			new_prop.transform.pos.x = viewport_norm.x;
			new_prop.transform.pos.x -= ((transform.origin.x + 1.0) * ((m_full_x / 2) * transform.scale.x));
			new_prop.transform.pos.x += (xpos + glyph->offset.x * transform.scale.x);
			new_prop.transform.pos.x /= (((f32)SPWindow::getWidth() / 2) / SP_UNIT_PIXELS);

			new_prop.transform.pos.y = viewport_norm.y + ((glyph->offset.y * transform.scale.y));
			new_prop.transform.pos.y += (((m_largest_y / 2) * ((transform.origin.y + 1.0) * transform.scale.y)) / SP_UNIT_PIXELS);
			new_prop.transform.pos.y /= -(((f32)SPWindow::getHeight() / 2) / SP_UNIT_PIXELS);

		}

		xpos += glyph->advance * transform.scale.x;

		new_prop.transform.scale.x = transform.scale.x;
		new_prop.transform.scale.y = transform.scale.y;
		new_prop.transform.layer = transform.layer;

		frame.renderables.push_back(new_prop.renderable(camera));

		// NOTE: This migtht explode with fonts that have the OPS(or whatever it is called) table and not a kerning table. Dont forget
		if ((i + 1) < m_glyphs.size()) {
			xpos += (SPFontCache::kernOffset(glyph, &m_glyphs[i + 1]) / SP_UNIT_PIXELS) * transform.scale.x;
		}

	}
}

void SPRenderText::set(std::string text) {
	m_full_x = 0.0f;
	m_largest_y = 0.0f;
	m_glyphs.reserve(text.size());
	m_glyphs.resize(0);
	for (char& c : text) {
		m_glyphs.push_back(SPFontCache::fetchGlyph(c));
	}
	for (int i = 0; i < m_glyphs.size(); i++) {
		SPGlyph* glyph = &m_glyphs[i];
		m_full_x += glyph->advance * transform.scale.x;
		if (glyph->sprite.size_exact.y > m_largest_y) {
			m_largest_y = (glyph->sprite.size_exact.y);
		}
	}
}