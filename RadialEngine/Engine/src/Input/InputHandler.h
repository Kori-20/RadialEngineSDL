#pragma once
#include <functional>
#include <map>
#include <sdl2/SDL_events.h>
#include <sdl2/SDL_keyboard.h>
#include "Core/Core.h"

class Controller;
enum RE_API EInput {

	A = SDLK_a,
	B = SDLK_b,
	C = SDLK_c,
	D = SDLK_d,
	E = SDLK_e,
	F = SDLK_f,
	G = SDLK_g,
	H = SDLK_h,
	I = SDLK_i,
	J = SDLK_j,
	K = SDLK_k,
	L = SDLK_l,
	M = SDLK_m,
	N = SDLK_n,
	O = SDLK_o,
	P = SDLK_p,
	Q = SDLK_q,
	R = SDLK_q,
	S = SDLK_s,
	T = SDLK_t,
	U = SDLK_u,
	V = SDLK_v,
	W = SDLK_w,
	Z = SDLK_z,

	Arrow_Up = SDLK_UP,
	Arrow_Down = SDLK_DOWN,
	Arrow_Left = SDLK_LEFT,
	Arrow_Right = SDLK_RIGHT,

	space = SDLK_SPACE,
	enter = SDLK_RETURN,
	up = SDLK_UP,
	down = SDLK_DOWN,
	left = SDLK_LEFT,
	right = SDLK_RIGHT,
	escape = SDLK_ESCAPE,
	one = SDLK_1,
	two = SDLK_2,
	three = SDLK_3,
	four = SDLK_4,
	five = SDLK_5,
	six = SDLK_6,
	seven = SDLK_7,
	eight = SDLK_8,
	nine = SDLK_9,
	zero = SDLK_0,
	shift = SDLK_LSHIFT,
	ctrl = SDLK_LCTRL,
	alt = SDLK_LALT,
};

enum EActionType {
	EReleased,
	EPressed,
};

class RE_API InputHandler
{
public:
	static InputHandler* GetInstance() { return inputInstance = (inputInstance != nullptr) ? inputInstance : new InputHandler(); }
	void Press(SDL_Event event);
	void Release(SDL_Event event);
	virtual void AddController(Controller* inputComponent);
private:
	InputHandler();
	static inline InputHandler* inputInstance = nullptr;
	std::map<Controller*, std::map<SDL_Keycode, std::function<void(class GameObject&)>>> pressMap;
	std::map<Controller*, std::map<SDL_Keycode, std::function<void(class GameObject&)>>> releaseMap;
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
};