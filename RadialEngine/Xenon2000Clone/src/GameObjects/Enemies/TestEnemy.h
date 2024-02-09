#pragma once
#include "OpenGL/SpriteComponent.h"
#include "Physics/BoxCollision.h"
#include "Physics/RigidBody.h"
#include "OpenGL/AnimatorComponent.h"
#include "ECS/GameObject.h"
#include "ECS/TextComponent.h"

class TestEnemy : public GameObject
{
public:
	TestEnemy(float x, float y);
	~TestEnemy() = default;

	void Update(float deltaTime) override;

	void TakeDamage(float damage);

	bool move = true;

protected:
	SpriteComponent* enemySprite;
	BoxCollision* enemyBoxColli;
	RigidBody* enemyRb;
	AnimatorComponent* enemyAc;

	Vector2D moveDirection = Vector2D(-50, 0); // Start moving to the left
	float moveSpeed = 50.0f;
	float timer = 0.0f;
	float switchInterval = 2.0f; // Time interval to switch direction

	float hp = 10;
};

