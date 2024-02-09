#pragma once

#include <functional>
#include <map>

#include <sdl2/SDL_scancode.h>
#include "Core/Core.h"
#include "ECS/Component.h"
#include "Input/InputHandler.h"


class RE_API Controller : public Component {
public:
	// Method to bind a key to a specific function
	std::map<SDL_Scancode, std::function<void(class GameObject&)>> get_inputs() { return pressedKey; }
	std::map<SDL_Scancode, std::function<void(class GameObject&)>> get_releases() { return releasedKey; }

	void BindPressed(EInput key, std::function<void(class GameObject&)>gameFunction);
	void BindReleased(EInput key, std::function<void(class GameObject&)>gameFunction);

	void BindKey(EActionType _type, EInput key, void(GameObject::* gameFunction)());

	//TODO: vector inputs;

	Controller();

	class InputHandler* GetInputHandler() const { return my_handler; }
private:
	std::map<SDL_Scancode, std::function<void(class GameObject&)>> pressedKey;
	std::map<SDL_Scancode, std::function<void(class GameObject&)>> releasedKey;

	class InputHandler* my_handler;
};



