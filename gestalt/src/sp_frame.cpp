
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
	m_frame_alarm = SPAlarm(((f32)1 / (f32)fps));
}

b32 SPFrame::ready() {
	b32 result = false;
	result = m_frame_alarm.triggered();
	if (result) {
		m_frame_alarm.reset();
	}
	return result;
}