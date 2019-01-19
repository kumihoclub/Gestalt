
#include "sp_window.h"
#include "sp_input_manager.h"
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

SPWindow window;
SPInputManager input;
SPRenderer render;

SPFrame frame;
SPViewport viewport;

SPShaderCache shader_cache;
SPSpriteCache sprite_cache;
SPFontCache font_cache;

int main(int argc, char *argv[]) {

	viewport.size = { 960.0f, 540.0f };
	frame.set_lock(60);

	window.init("Black Telephone", viewport);
	shader_cache.init();
	sprite_cache.init();
	font_cache.init();
	input.init();
	render.init();

	window.show();

	//sprite_cache.init();
	while (!input.quitEvent()) {
		if (frame.ready()) {
			window.update(viewport);
			input.update();

			// DEBUG

			SPCamera test_camera;
			//test_camera.pos.y += 8;

			SPRenderText test_text("Hi Mom.");
			test_text.transform.anchor = SP_ANCHOR_VIEWPORT;
			test_text.transform.pos = { -1.0f, 1.0f };
			test_text.transform.scale = { 1.0f, 1.0f };
			test_text.transform.origin = { -1.0, 1.0 };

			test_text.build(frame, test_camera, viewport);

			//SPCamera test_camera;
			//test_camera.pos.y += 8;
			
			/*SPProp test_prop;
			SPMaterial new_mat;
			test_prop.transform.pos = { -1.0, -1.0 };
			test_prop.transform.anchor = SP_ANCHOR_WORLD;
			new_mat.shader = SPShaderCache::fetchShader("sprite_default");
			new_mat.sprite = SPSpriteCache::fetchSprite("sad_cat.png");
			test_prop.material = new_mat;
			test_prop.transform.origin = { -1.0, 1.0 };
			frame.renderables.push_back(test_prop.renderable(test_camera, viewport));*/
			

			//test_prop.sprite.get().color.r = 1.0;
			//test_prop.sprite.get().color.g = 0.5;
			//test_prop.sprite.get().color.b = 0.5;
			//test_prop.sprite.get().color.a = 0.25;

			//SPRenderable test_renderable(test_prop, test_camera, viewport);

			//frame.renderables.push_back(test_prop.renderable(test_camera, viewport));

			// END DEBUG

			window.clear();
			frame.sort();
			render.draw(frame);
			window.swap();
			frame.reset();
		}
	}
	//sprite_cache.shutdown();

	window.hide();

	render.shutdown();
	input.shutdown();
	font_cache.shutdown();
	sprite_cache.shutdown();
	shader_cache.shutdown();
	window.shutdown();

	return 0;

}