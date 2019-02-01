
#include "sp_window.h"
#include "sp_renderer.h"

#include "sp_frame.h"
#include "sp_viewport.h"

#include "sp_sprite_cache.h"
#include "sp_font_cache.h"
#include "sp_shader_cache.h"

#include "sp_render_text.h"

#include <iostream>
#include <vector>
#include <chrono>

#include "SDL2/SDL.h"

// SIM
#include "test_sim.h"
TestSim sim;
//

SPWindow window;
SPRenderer render;

SPFrame frame;
SPViewport viewport;

SPShaderCache shader_cache;
SPSpriteCache sprite_cache;
SPFontCache font_cache;

int main(int argc, char *argv[]) {

	viewport.size = { 960.0f, 540.0f };
	frame.set_lock(60);

	window.init("Sadcat.exe", viewport);
	shader_cache.init();
	sprite_cache.init();
	font_cache.init(true);
	render.init();
	sim.init();

	window.show();

	while (!window.quitEvent()) {
		if (frame.ready()) {
			window.update(viewport);
			sim.update(viewport, frame);
			window.clear();
			frame.sort();
			render.draw(frame);
			window.swap();
			frame.reset();
		}
	}

	window.hide();

	sim.shutdown();

	render.shutdown();
	font_cache.shutdown();
	sprite_cache.shutdown();
	shader_cache.shutdown();
	window.shutdown();

	return 0;

}