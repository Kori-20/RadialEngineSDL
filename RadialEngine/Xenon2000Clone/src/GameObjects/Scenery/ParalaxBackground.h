#pragma once
#include "ECS/GameObject.h"
#include "OpenGL/SpriteComponent.h"

class ParalaxBackground : public GameObject
{
public:
	ParalaxBackground(const std::string& path,float w, float h, int s, float speed, float yPos);
	ParalaxBackground();
	~ParalaxBackground();

	void Update(float deltaTime) override;

private:
	SpriteComponent* paralLayerFront;
	SpriteComponent* paralLayerBack;

	float parallaxSpeed = 30;
};

