
class PlayerController : SPBehavior {
	vec2 vel;
	void start() {
		//spFindActor("player");
	}
	void pre_tick() {
		SPKeyState w_state = spGetKeyState(KEYCODE_W);
		SPKeyState a_state = spGetKeyState(KEYCODE_A);
		SPKeyState s_state = spGetKeyState(KEYCODE_S);
		SPKeyState d_state = spGetKeyState(KEYCODE_D);
		if(w_state == KEYSTATE_PRESSED) {
			vel.y -= 5.0;
		} else if(w_state == KEYSTATE_RELEASED) {
			vel.y += 5.0;
		}
		if(a_state == KEYSTATE_PRESSED) {
			vel.x -= 5.0;
		} else if(a_state == KEYSTATE_RELEASED) {
			vel.x += 5.0;
		}
		if(s_state == KEYSTATE_PRESSED) {
			vel.y += 5.0;
		} else if(s_state == KEYSTATE_RELEASED) {
			vel.y -= 5.0;
		}
		if(d_state== KEYSTATE_PRESSED) {
			vel.x += 5.0;
		} else if(d_state == KEYSTATE_RELEASED) {
			vel.x -= 5.0;
		}
		spSetLinearVel(vel);
	}
	void post_tick() {
		
	}
}