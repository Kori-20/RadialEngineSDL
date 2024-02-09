#include "Controller.h"

#include <iostream>
#include <utility>

#include "Core/EngineCore.h"
#include "ECS/GameObject.h"


////////////////////////////////////////////////////////
///
/// Input Component
///
////////////////////////////////////////////////////////


void Controller::BindPressed(EInput key, std::function<void(GameObject&)> _function) {
	const auto scan = static_cast<SDL_Scancode>(key);
	pressedKey[scan] = std::move(_function);

}

void Controller::BindReleased(EInput key, std::function<void(GameObject&)> _function) {
	const auto scan = static_cast<SDL_Scancode>(key);
	releasedKey[scan] = std::move(_function);
}


void Controller::BindKey(EActionType _type, EInput key, void(GameObject::* _function)()) {
	switch (_type) {
	case EReleased: {
		const auto a = std::function<void(GameObject&)>(_function);
		BindReleased(key, a);
		break;
	}

	case EActionType::EPressed:
	default: {
		const auto a = std::function<void(GameObject&)>(_function);
		BindPressed(key, a);
		break;
	}
	}

}

Controller::Controller() {
	my_handler = EngineCore::GetInstance()->GetInputHandler();
}
