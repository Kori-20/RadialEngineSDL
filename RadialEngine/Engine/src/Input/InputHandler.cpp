
#include "InputHandler.h"

#include <iostream>
#include <sdl2/SDL_events.h>

#include "Controller.h"
#include "ECS/GameObject.h"
#include "Aid/Logger.h"

InputHandler::InputHandler() 
{
	Logger::Display("Input Handler created");
}

void InputHandler::Press(SDL_Event event) {
	for (const auto it : pressMap) {
		const auto inputComponent = it.first;
		std::map<SDL_Keycode, std::function<void(GameObject&)>> componentMap = it.second;
		auto func = componentMap.find(event.key.keysym.sym);
		if (func != componentMap.end()) {
			auto gameObject = dynamic_cast<GameObject*>(inputComponent->GetOwner());
			if (gameObject) {
				keyState[event.key.keysym.sym];
				(func->second)(*gameObject);
			}
		}
	}
}

void InputHandler::Release(SDL_Event event) {
	for (const auto it : releaseMap) {
		const auto inputComponent = it.first;
		std::map<SDL_Keycode, std::function<void(GameObject&)>> componentMap = it.second;
		auto func = componentMap.find(event.key.keysym.sym);
		if (func != componentMap.end()) {
			auto gameObject = dynamic_cast<GameObject*>(inputComponent->GetOwner());
			if (gameObject) {
				//keyState = SDL_GetKeyboardState(nullptr)
				(func->second)(*gameObject);
			}
		}
	}
}

void InputHandler::AddController(Controller* inputComponent) {

	const std::map<SDL_Scancode, std::function<void(GameObject&)>> releases = inputComponent->get_releases();
	for (const auto& pree : releases) {
		releaseMap[inputComponent][pree.first] = pree.second;
	}

	const std::map<SDL_Scancode, std::function<void(GameObject&)>> inputs = inputComponent->get_inputs();
	for (const auto& key_binding : inputs) {
		pressMap[inputComponent][key_binding.first] = key_binding.second;
	}
}
