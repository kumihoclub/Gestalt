#pragma once

#include "sp_common.h"
#include "sp_renderable.h"

#include "SDL2/SDL.h"

class SPWindow {
public:
	void init(const char* title, u32 width, u32 height);
	void shutdown();
	void update();
	void clear();
	void swap();
	void show();
	void hide();
	b32 quitEvent();
	static void setScale(u32 scale);
	static u32 getScale();
	static u32 getWidth();
	static u32 getHeight();
};