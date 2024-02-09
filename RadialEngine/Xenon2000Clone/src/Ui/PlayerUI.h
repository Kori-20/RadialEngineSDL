#pragma once
#include "ECS/GameObject.h"
#include "ECS/TextComponent.h"
#include "OpenGL/SpriteComponent.h"

class PlayerUI : public GameObject
{
	public:
	PlayerUI();
	~PlayerUI();

	void UpdateUiValues(TextComponent uiElement, std::string newValue);

private:
	SpriteComponent* HpBar;
	SpriteComponent* HpBarBorder;
	SpriteComponent* heart1;
	SpriteComponent* heart2;
	SpriteComponent* heart3;
};

