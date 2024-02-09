#include "TestEnemy.h"
#include "../../Managers/ScoreManager.h"
#include "Level/LevelManager.h"

TestEnemy::TestEnemy(float x, float y)
{
	AddTag(Enemy);
	transform->SetPosition(x, y);

	enemySprite = &AddComponent<SpriteComponent>("Assets/clone.bmp", 32.f/128.f /2, 32.f/160.f /2, 1);//new openGl sprite
	enemySprite->numberOfCollums = 5;
	enemySprite->numberOfRows = 4;
	enemySprite->isAnimated = true;

	enemyAc = &AddComponent<AnimatorComponent>(enemySprite);
	enemyAc->SetAnimParameters(1, 4, 1.f, true);
	enemyAc->numberOfRows = 5;
	enemyAc->numberOfCollums = 4;

	enemyBoxColli = &AddComponent<BoxCollision>(Vector2D(20,20));
	enemyBoxColli->SetFilterCollision(EnemyF);
	enemyBoxColli->SetFilterMasking(EnemyMask);
	
	enemyRb = &AddComponent<RigidBody>();
	enemyRb->SetCollider(enemyBoxColli);
	enemyRb->afectedByGravity = false;
	enemyRb->bodyType = EBodyType::KinematicB;

	//enemyRb = &AddComponent<RigidBodyComponent>();
}

void TestEnemy::Update(float deltaTime) {
	GameObject::Update(deltaTime);
	if (move) 
	{
		// Accumulate the timer
		timer += deltaTime;

		// Check if it's time to switch direction
		if (timer >= switchInterval)
		{
			// Switch direction
			moveDirection.x = -moveDirection.x; // Flip the x-component of the direction vector
			timer -= switchInterval; // Reset the timer
		}

		// Move the enemy
		enemyRb->Move(moveDirection, moveSpeed);
	}
}

void TestEnemy::TakeDamage(float damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		ScoreManager::GetInstance().AddScore(100);
		LevelManager::getInstance().GetCurrentLevel()->RemoveGameObject(this);
	}
}

