
#include "game_state.h"

void GameState::onEnter() {

	step_alarm.resume();
	step_alarm.reset();

	game_state_text.set("Game State");
	game_state_text.transform.scale = { 0.25f, 0.25f };
	game_state_text.transform.anchor = SP_ANCHOR_VIEWPORT;
	game_state_text.transform.pos = { 0.0f, 0.95f };
	game_state_text.transform.origin = { 0.0f, 1.0f };
	game_state_text.transform.layer = 16.0;

	instruction_text.set("WASD = MOVE : ARROW UP/DOWN = SCALE : ARROW LEFT/RIGHT = CAMERA");
	instruction_text.transform.scale = { 0.15f, 0.15f };
	instruction_text.transform.anchor = SP_ANCHOR_VIEWPORT;
	instruction_text.transform.pos = { 0.0f, -0.95f };
	instruction_text.transform.origin = { 0.0f, -1.0f };
	instruction_text.transform.layer = 16.0;

	up_frames[0] = SPDatabase::fetchSprite("mako_world_up_1");
	left_frames[0] = SPDatabase::fetchSprite("mako_world_left_1");
	right_frames[0] = SPDatabase::fetchSprite("mako_world_right_1");
	down_frames[0] = SPDatabase::fetchSprite("mako_world_down_1");

	up_frames[1] = SPDatabase::fetchSprite("mako_world_up_2");
	left_frames[1] = SPDatabase::fetchSprite("mako_world_left_2");
	right_frames[1] = SPDatabase::fetchSprite("mako_world_right_2");
	down_frames[1] = SPDatabase::fetchSprite("mako_world_down_2");

	up_frames[2] = SPDatabase::fetchSprite("mako_world_up_1");
	left_frames[2] = SPDatabase::fetchSprite("mako_world_left_1");
	right_frames[2] = SPDatabase::fetchSprite("mako_world_right_1");
	down_frames[2] = SPDatabase::fetchSprite("mako_world_down_1");

	up_frames[3] = SPDatabase::fetchSprite("mako_world_up_3");
	left_frames[3] = SPDatabase::fetchSprite("mako_world_left_3");
	right_frames[3] = SPDatabase::fetchSprite("mako_world_right_3");
	down_frames[3] = SPDatabase::fetchSprite("mako_world_down_3");

	target_frame = 0;

	SPMaterial mat;
	mat.shader = SPShaderCache::fetchShader("sprite_default");
	mat.sprite = down_frames[0];

	mako_prop.material = mat;

	//mako_prop.transform.scale = { 3.0f, 3.0f };

	target_frames = down_frames;
	camera.scale = 3.0;
	step_alarm.set(0.1);

}

void GameState::update(SPViewport& view, SPFrame& frame, SPTransitionStack* transition_stack) {

	glm::vec2 vel = { 0.0f, 0.0f };

	if (up.pressed() || up.held()) {
		vel.y -= 0.1;
		target_frames = up_frames;
	}
	if (left.pressed() || left.held()) {
		vel.x -= 0.1;
		target_frames = left_frames;
	}
	if (right.pressed() || right.held()) {
		vel.x += 0.1;
		target_frames = right_frames;
	}
	if (down.pressed() || down.held()) {
		vel.y += 0.1;
		target_frames = down_frames;
	}

	//DEBUG

	SPKeyboardKey arrow_right = SPKeyboardKey(SDL_SCANCODE_RIGHT);
	SPKeyboardKey arrow_left = SPKeyboardKey(SDL_SCANCODE_LEFT);

	if (arrow_up.pressed()) {
		view.scale += 1;
	}
	else if (arrow_down.pressed()) {
		if (view.scale != 1) {
			view.scale -= 1;
		}
	}

	f32 cam_add = 0.0f;
	if (arrow_right.pressed() || arrow_right.held()) {
		cam_add += 0.1;
	}
	else if (arrow_left.pressed() || arrow_left.held()) {
		cam_add -= 0.1;
	}
	camera.pos.x += cam_add;

	//END DEBUG

	if (vel == glm::vec2(0.0f, 0.0f)) {
		step_alarm.reset();
		step_alarm.pause();
		target_frame = 0;
		mako_prop.material.val().sprite = target_frames[target_frame];
	}
	else if(step_alarm.paused()) {
		step_alarm.resume();
	}

	if (step_alarm.triggered()) {
		target_frame++;
		if (target_frame > 3) {
			target_frame = 0;
		}
		step_alarm.reset();
	}

	mako_prop.material.val().sprite = target_frames[target_frame];

	mako_prop.transform.pos += vel;

	frame.renderables.push_back(mako_prop.renderable(camera, view));
	game_state_text.build(frame, camera, view);
	instruction_text.build(frame, camera, view);

	SPKeyboardKey space = SPKeyboardKey(SDL_SCANCODE_SPACE);
	if (space.pressed()) {
		SPTransition transition;
		transition.type = SP_TRANSITION_TYPE_POP;
		transition_stack->push(transition);
	}
	
}

void GameState::onExit() {
	step_alarm.pause();
	step_alarm.reset();
}