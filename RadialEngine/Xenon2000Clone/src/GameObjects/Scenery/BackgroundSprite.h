#pragma once
#include "ECS\GameObject.h"
#include "OpenGL/SpriteComponent.h"

class BackgroundSprite : public GameObject
{
public:
	BackgroundSprite();
	~BackgroundSprite();

private:

		SpriteComponent* bckgSprite;
};

