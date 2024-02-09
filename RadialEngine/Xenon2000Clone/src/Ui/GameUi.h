#pragma once
#include "ECS/GameObject.h"
#include "ECS/TextComponent.h"

class GameUi : public GameObject
{
public:
	GameUi();
	~GameUi();

	void UpdateScore(int newValue);

private:
	TextComponent* playerOneText;
	TextComponent* currentScore;
	TextComponent* highScoreText;
	TextComponent* highScoreValue;
};

