#pragma once
#include "ECS/Pawn.h"
#include "Input/Controller.h"
//New openGl Stuff
#include "OpenGL/SpriteComponent.h"
#include "OpenGL/AnimatorComponent.h"
//Physics
#include "Physics/BoxCollision.h"
#include "Physics/RigidBody.h"

class PlayerShip : public Pawn
{
public:
	PlayerShip();

	void OnCollisionStart(GameObject* obj) override;
	void OnOverlapBegin(GameObject* obj) override;

	void Update(float deltaTime) override;

	void Heal(int amount);
	void TakeDamage(int dmgTaken);

	void GainLife();

	void LoseLife();
	void TempImortal(float duration);
	void Respawn();
	void YouLost();

protected:
	SpriteComponent* sprite; //Using opengl sprite
	BoxCollision* overlapBox;
	//BoxCollision* colliderBox;
	RigidBody* myRb;
	AnimatorComponent* ac;


	void Shoot();
	//Movement
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	//To stop rigidbody movement
	void StopXMove();
	void StopYMove();

private:

	int hp = 100;
	int lives = 3;

	//Define horizontal and vertical speed
	Vector2D speed;

	bool canShoot = true;
	float shotDelay = 0.65f;

	bool isImortal = false;
	bool isDead = false;
	bool isRespawning = false;

	float imortalityDuration = 0.25f; //activates every instance that the player takes damage
	float respawnDuration = 2.0f;
	
};


