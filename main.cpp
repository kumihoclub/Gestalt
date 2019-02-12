
#include "sp_window.h"
#include "sp_renderer.h"

#include "sp_frame.h"
#include "sp_viewport.h"

#include "sp_font_cache.h"
#include "sp_shader_cache.h"
#include "sp_database.h"

#include "sp_render_text.h"

#include <iostream>
#include <vector>
#include <chrono>

#include "SDL2/SDL.h"

// SIM
#include "bt_sim.h"
BTSim black_telephone;
//

SPWindow window;
SPRenderer render;

SPFrame frame;
SPViewport viewport;

SPShaderCache shader_cache;
SPFontCache font_cache;
SPDatabase database;

int main(int argc, char *argv[]) {

	viewport.size = { 480.0f, 270.0f };
	//viewport.size = { 1920, 1080 };
	//viewport.scale = 2;
	frame.set_lock(60);

	window.init("Sadcat.exe", viewport);
	shader_cache.init();
	font_cache.init(true);
	database.init();
	render.init();
	black_telephone.init();

	window.show();

	while (!window.quitEvent()) {
		if (frame.ready()) {
			window.update(viewport);
			black_telephone.update(viewport, frame);
			window.clear();
			frame.sort();
			render.draw(frame);
			window.swap();
			frame.reset();
		}
	}

	window.hide();

	black_telephone.shutdown();

	render.shutdown();
	database.shutdown();
	font_cache.shutdown();
	shader_cache.shutdown();
	window.shutdown();

	return 0;

}