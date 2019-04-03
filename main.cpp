
#include "sp_window.h"
#include "sp_renderer.h"

#include "sp_frame.h"

#include "sp_font_cache.h"
#include "sp_shader_cache.h"
#include "sp_database.h"

#include "sp_render_text.h"

#include <iostream>
#include <vector>
#include <chrono>

#include "SDL2/SDL.h"

// SIM
#include "test_sim.h"
TestSim test_sim;
//

SPWindow window;
SPRenderer render;

SPFrame frame;

SPShaderCache shader_cache;
SPFontCache font_cache;
SPDatabase database;

int main(int argc, char *argv[]) {

	frame.set_lock(60);

	window.init("Gestalt", 480, 270);
	shader_cache.init();
	font_cache.init(true);
	database.init();
	render.init();
	test_sim.init();

	window.show();

	while (!window.quitEvent()) {
		if (frame.ready()) {
			window.update();
			test_sim.update(frame);
			window.clear();
			frame.sort();
			render.draw(frame);
			window.swap();
			frame.reset();
		}
	}

	window.hide();

	test_sim.shutdown();

	render.shutdown();
	database.shutdown();
	font_cache.shutdown();
	shader_cache.shutdown();
	window.shutdown();

	return 0;

}