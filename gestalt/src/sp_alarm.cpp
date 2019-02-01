
#include "sp_alarm.h"

SPAlarm::SPAlarm() {

}

SPAlarm::SPAlarm(f32 time_ins_seconds) {
	set(time_ins_seconds);
}

void SPAlarm::set(f32 time_ins_seconds) {
	m_target_time = milliseconds(u32(time_ins_seconds * 1000));
	reset();
}

void SPAlarm::pause() {
	m_paused = true;
}

b32 SPAlarm::paused() {
	return m_paused;
}

void SPAlarm::resume() {
	m_paused = false;
	m_timestamp = high_res_clock::now();
}

void SPAlarm::reset() {
	m_paused = false;
	m_timestamp = high_res_clock::now();
	m_current_time = nanoseconds(0);
}

b32 SPAlarm::triggered() {
	b32 result = false;
	if (!m_paused) {
		auto delta = high_res_clock::now() - m_timestamp;
		m_timestamp = high_res_clock::now();
		m_current_time += std::chrono::duration_cast<nanoseconds>(delta);
		if (m_current_time > m_target_time) {
			result =  true;
		}
	}
	return result;
}

b32 SPAlarm::triggered(f32& percentage) {
	b32 result = triggered();
	percentage = (m_current_time * 100 / m_target_time);
	if (percentage > 100) percentage = 100;
	percentage /= (f32)100;
	//Casting to 0.0-1.0 float for easier use
	return result;
}
