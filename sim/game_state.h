#pragma once

#include "sp_sim.h"
#include "sp_prop.h"
#include "sp_render_text.h"
#include "sp_camera.h"
#include "sp_font_cache.h"
#include "sp_database.h"
#include "sp_shader_cache.h"
#include "sp_alarm.h"
#include "sp_input.h"
#include "sp_transition.h"
#include "sp_state.h"

#include "SDL2/SDL.h"

class GameState : public SPState {
public:
	void onEnter();
	void update(SPFrame& frame, SPTransitionStack* transition_stack);
	void onExit();

private:

	SPCamera camera;
	SPProp mako_prop;

	SPSprite up_frames[4];
	SPSprite left_frames[4];
	SPSprite right_frames[4];
	SPSprite down_frames[4];
	SPSprite* target_frames = nullptr;

	SPKeyboardKey up = { SDL_SCANCODE_W };
	SPKeyboardKey left = SPKeyboardKey(SDL_SCANCODE_A);
	SPKeyboardKey down = SPKeyboardKey(SDL_SCANCODE_S);
	SPKeyboardKey right = SPKeyboardKey(SDL_SCANCODE_D);

	SPRenderText game_state_text;
	SPRenderText instruction_text;

	//DEBUG
	SPKeyboardKey arrow_up = SPKeyboardKey(SDL_SCANCODE_UP);
	SPKeyboardKey arrow_down = SPKeyboardKey(SDL_SCANCODE_DOWN);
	//END DEBUG

	SPAlarm step_alarm;

	i32 view_scale = 1;

	u32 target_frame = 0;

};
