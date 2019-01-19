
#include "sp_frame.h"
#include "sp_sprite.h"

#include <algorithm>

void SPFrame::reset() {
	renderables.resize(0);
}

void SPFrame::sort() {
	std::sort(renderables.begin(), renderables.end(), [](const SPRenderable& a, const SPRenderable& b) -> bool
	{
		if (a.layer < b.layer)
			return true;
		else if (b.layer < a.layer)
			return false;
		else // name equals.
			if (a.material.sprite.image_id < b.material.sprite.image_id)
				return true;
			else if (b.material.sprite.image_id < a.material.sprite.image_id)
				return false;
	});
}

void SPFrame::set_lock(u32 fps) {
	m_target_time = milliseconds(u32(((f32)1 / (f32)fps) * 1000));
	m_timestamp = high_res_clock::now();
}

b32 SPFrame::ready() {
	auto delta = high_res_clock::now() - m_timestamp;
	m_timestamp = high_res_clock::now();
	m_current_time += std::chrono::duration_cast<nanoseconds>(delta);
	if (m_current_time > m_target_time) {
		m_current_time = nanoseconds(0);
		return true;
	}
	return false;
}