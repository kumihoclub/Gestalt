
#include "test_sim.h"

void TestSim::init() {

	SPMaterial arena_material;
	arena_material.sprite = SPSpriteCache::fetchSprite("test_arena.png");
	arena_material.shader = SPShaderCache::fetchShader("sprite_default");
	arena_material.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_arena_background.material = arena_material;
	m_arena_background.transform.anchor = SP_ANCHOR_VIEWPORT;
	m_arena_background.transform.origin = { -1.0, 1.0 };
	m_arena_background.transform.pos = { -1.0, 1.0 };

	SPMaterial player_material;
	player_material.shader = SPShaderCache::fetchShader("sprite_default");
	player_material.sprite = SPSpriteCache::fetchSprite("sadcat.png");
	player_material.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_sadcat_a.material = player_material;
	m_sadcat_b.material = player_material;
	m_sadcat_c.material = player_material;

	m_sadcat_a.transform.scale = { 1.0f, 1.0f };
	m_sadcat_b.transform.scale = { 1.0f, 1.0f };
	m_sadcat_c.transform.scale = { 1.0f, 1.0f };

	m_sadtext_a.transform.scale = { 0.4f, 0.4f };
	m_sadtext_b.transform.scale = { 0.4f, 0.4f };
	m_sadtext_c.transform.scale = { 0.4f, 0.4f };

	m_sadcat_a.transform.pos.x -= 8;
	m_sadcat_c.transform.pos.x += 8;

	m_sadcat_a.transform.pos.y += 5;
	m_sadcat_b.transform.pos.y += 5;
	m_sadcat_c.transform.pos.y += 5;

	m_sadcat_a.material.get().flipped = true;

	m_sadtext_a.transform.pos = m_sadcat_a.transform.pos;
	m_sadtext_b.transform.pos = m_sadcat_b.transform.pos;
	m_sadtext_c.transform.pos = m_sadcat_c.transform.pos;

	m_sadtext_a.transform.pos.y -= 1.6;
	m_sadtext_b.transform.pos.y -= 1.6;
	m_sadtext_c.transform.pos.y -= 1.6;

	//m_sadtext_a.transform.pos.x -= 0.75f;
	//m_sadtext_b.transform.pos.x -= 0.75f;
	//m_sadtext_c.transform.pos.x -= 0.75f;

	m_sadtext_a.set("(0/100)");
	m_sadtext_b.set("(0/100)");
	m_sadtext_c.set("(0/100)");

	f32 sadrand_a = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f));
	f32 sadrand_b = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f));
	f32 sadrand_c = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f));

	m_sadalarm_a.set(sadrand_a);
	m_sadalarm_b.set(sadrand_b);
	m_sadalarm_c.set(sadrand_c);

	asdf.set("AyElmAo420!");

}

void TestSim::update(SPViewport& view, SPFrame& frame) {

	f32 sadresult_a, sadresult_b, sadresult_c;
	b32 pause = false;
	if (m_sadalarm_a.triggered(sadresult_a)) {
		f32 sadrand_a = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f));
		m_sadalarm_a.set(sadrand_a);
	}
	if (m_sadalarm_b.triggered(sadresult_b)) {
		f32 sadrand_b = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f));
		m_sadalarm_b.set(sadrand_b);
	}
	if (m_sadalarm_c.triggered(sadresult_c)) {
		f32 sadrand_c = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f));
		m_sadalarm_c.set(sadrand_c);
	}

	m_sadtext_a.set("(" + std::to_string((u32)(sadresult_a * 100)) + "/100)");
	m_sadtext_b.set("(" + std::to_string((u32)(sadresult_b * 100)) + "/100)");
	m_sadtext_c.set("(" + std::to_string((u32)(sadresult_c * 100)) + "/100)");

	frame.renderables.push_back(m_sadcat_a.renderable(m_camera, view));
	frame.renderables.push_back(m_sadcat_b.renderable(m_camera, view));
	frame.renderables.push_back(m_sadcat_c.renderable(m_camera, view));

	frame.renderables.push_back(m_arena_background.renderable(m_camera, view));

	m_sadtext_a.build(frame, m_camera, view);
	m_sadtext_b.build(frame, m_camera, view);
	m_sadtext_c.build(frame, m_camera, view);

	asdf.build(frame, m_camera, view);

}

void TestSim::shutdown() {

}