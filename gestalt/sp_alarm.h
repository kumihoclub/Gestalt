#pragma once

/*
	Alarms are used for executing/tracking things on timed intervals. Used internaly by SPFrame for framelocking, and can be used for gameplay as well.
*/

#include "sp_common.h"

#include <chrono>

using high_res_clock = std::chrono::high_resolution_clock;
using timestamp = std::chrono::time_point<std::chrono::high_resolution_clock>;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

// Time is in seconds

class SPAlarm {
public:
	SPAlarm();
	SPAlarm(f32 time_ins_seconds);
	void set(f32 time_ins_seconds);
	void pause();
	void resume();
	b32 paused();
	void reset();
	b32 triggered();
	b32 triggered(f32& percentage);
private:
	milliseconds m_target_time;
	nanoseconds m_current_time;
	timestamp m_timestamp;
	f32 m_time_raw = 0.0f;
	b32 m_paused = false;
};