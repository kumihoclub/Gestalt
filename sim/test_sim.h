#pragma once

#include "sp_sim.h"
#include "sp_prop.h"
#include "sp_render_text.h"
#include "sp_camera.h"
#include "sp_font_cache.h"
#include "sp_sprite_cache.h"
#include "sp_shader_cache.h"
#include "sp_alarm.h"

class TestSim : public SPSim {
public:
	void init();
	void update(SPViewport& view, SPFrame& frame);
	void shutdown();

private:
	SPCamera m_camera;
	SPProp m_sadcat_a;
	SPProp m_sadcat_b;
	SPProp m_sadcat_c;
	SPProp m_arena_background;
	SPRenderText m_sadtext_a;
	SPRenderText m_sadtext_b;
	SPRenderText m_sadtext_c;
	SPRenderText asdf;
	SPAlarm m_sadalarm_a;
	SPAlarm m_sadalarm_b;
	SPAlarm m_sadalarm_c;

};