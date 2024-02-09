#pragma once
#include "ECS/GameObject.h"
#include "OpenGL/SpriteComponent.h"
#include <Physics/BoxCollision.h>
#include <Physics/RigidBody.h>

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	void OnCollisionStart(GameObject* obj) override;
	void OnOverlapBegin(GameObject* obj) override;
	void OnOverlapEnd(GameObject* obj) override;

	void Update(float deltaTime) override;

	float pelletDamage = 5;

	bool isDead = false;

protected:
	SpriteComponent* bulletSprite;
	BoxCollision* bulletBox;
	RigidBody* bulletRb;

	
	int pelletSpeed = 10000;
	bool goUp = true;

	float bulletlifeTime = 0;
};

