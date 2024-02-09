#pragma once
#include "ECS/GameObject.h"
#include "Physics/RigidBody.h"
#include "Physics/BoxCollision.h"
#include "OpenGL/SpriteComponent.h"
#include "OpenGL/AnimatorComponent.h"


class Rock1 : public GameObject
{
public:
	Rock1();
	~Rock1();

	void Update(float deltaTime) override;

protected:
	SpriteComponent* sprite;
	RigidBody* myRb;
	BoxCollision* overlapBox;

private:

	float rockSpeed = 30.f;
};

