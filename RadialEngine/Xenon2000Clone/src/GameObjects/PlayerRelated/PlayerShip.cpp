#include "PlayerShip.h"
#include "Input/Controller.h"
#include "Level/LevelManager.h"
#include "../Bullet.h"
#include "UserInterface/Font.h"
#include "UserInterface/TextUI.h"
#include "../../Managers/ScoreManager.h"

float bulletCD = 0;

PlayerShip::PlayerShip() : Pawn()
{
	AddTag(Player);
	transform->SetPosition(360, 500);
	speed = Vector2D(450, 450);

	overlapBox = &AddComponent<BoxCollision>(Vector2D(20, 30));
	overlapBox->SetFilterMasking(PlayerMask);
	overlapBox->SetFilterCollision(PlayerF);

	/*
	colliderBox = &AddComponent<BoxCollision>(Vector2D(10, 40));
	colliderBox->SetFilterMasking(PlayerMask);
	colliderBox->SetFilterCollision(PlayerF);
	colliderBox->_sensor = false;
	*/

	myRb = &AddComponent<RigidBody>();
	myRb->SetCollider(overlapBox);
	myRb->afectedByGravity = false;

	sprite = &AddComponent<SpriteComponent>("Assets/PULife.bmp", .2, .2, 1);//new openGl sprite
	SetLayer(90);
	sprite->numberOfCollums= 1;
	sprite->numberOfRows = 1;
	sprite->isAnimated = false;

	pawnController->BindKey(EPressed, space, static_cast<void(GameObject::*)()>(&PlayerShip::Shoot));

	pawnController->BindKey(EPressed, D, static_cast<void(GameObject::*)()>(&PlayerShip::MoveRight));
	pawnController->BindKey(EPressed, A, static_cast<void(GameObject::*)()>(&PlayerShip::MoveLeft));
	pawnController->BindKey(EPressed, W, static_cast<void(GameObject::*)()>(&PlayerShip::MoveUp));
	pawnController->BindKey(EPressed, S, static_cast<void(GameObject::*)()>(&PlayerShip::MoveDown));

	pawnController->BindKey(EReleased, D, static_cast<void(GameObject::*)()>(&PlayerShip::StopXMove));
	pawnController->BindKey(EReleased, A, static_cast<void(GameObject::*)()>(&PlayerShip::StopXMove));
	pawnController->BindKey(EReleased, W, static_cast<void(GameObject::*)()>(&PlayerShip::StopYMove));
	pawnController->BindKey(EReleased, S, static_cast<void(GameObject::*)()>(&PlayerShip::StopYMove));

	pawnController->GetInputHandler()->AddController(pawnController);
}

void PlayerShip::OnCollisionStart(GameObject* obj)
{
	Logger::Info("Collided");
}

void PlayerShip::OnOverlapBegin(GameObject* obj)
{
	Logger::Info("Overlaped");
}

void PlayerShip::Update(float deltaTime)
{
	Pawn::Update(deltaTime);

	//Quick bullet spam fix
	if (!canShoot) 
	{
		bulletCD += deltaTime;
		if (bulletCD >= shotDelay) 
		{
			canShoot = true;
			bulletCD = 0;
		}
	}
}

void PlayerShip::Heal(int amount)
{
	if (hp + amount >= 100)
	{
		hp = 100;
	}
	else
	{
		hp += amount;
	}
}

void PlayerShip::TakeDamage(int dmgTaken)
{
	if (hp - dmgTaken <= 0) 
	{
		LoseLife();
	}
	else 
	{
		hp -= dmgTaken;
	}

	TempImortal(imortalityDuration);
}

void PlayerShip::GainLife()
{
	if (lives + 1 >= 3)
	{
		lives = 3;
		hp = 100; //heal to full if lives are full
	}
	else
	{
		lives++;
	}
}

void PlayerShip::LoseLife()
{
	if (lives - 1 <= 0)
	{
		YouLost();
	}
	else
	{
		lives--;
		Respawn();
	}
}

void PlayerShip::TempImortal(float duration)
{
	isImortal = true;

	//wait imortalityDuration;

	isImortal = false;
}

void PlayerShip::Respawn()
{
	TempImortal(imortalityDuration * 4);// = 1 second
	//set location to spawn location
}

void PlayerShip::YouLost()
{
	Logger::Info("You lost!");
}

void PlayerShip::Shoot()
{
	//Logger::Warning("Shoot");
	if (canShoot)
	{
		//Logger::Warning("Shoot");
		auto playerBullet = LevelManager::getInstance().InstantiateObject<Bullet>(Vector2D(transform->GetPosition().x + 30, transform->GetPosition().y + -55), *this);
		playerBullet.pelletDamage = 10;
		canShoot = false;
	}
}

void PlayerShip::MoveRight()
{
	myRb->Move(Vector2D(speed.x, myRb->GetVelocity().y), speed.x);
}

void PlayerShip::MoveLeft()
{
	myRb->Move(Vector2D(-speed.x, myRb->GetVelocity().y),speed.x);
}

void PlayerShip::MoveUp()
{
	myRb->Move(Vector2D(myRb->GetVelocity().x, -speed.y),speed.y);
}

void PlayerShip::MoveDown()
{
	myRb->Move(Vector2D(myRb->GetVelocity().x, speed.y),speed.y);
}

void PlayerShip::StopXMove()
{
	myRb->Move(Vector2D(0, myRb->GetVelocity().y),speed.y);
}

void PlayerShip::StopYMove()
{
	myRb->Move(Vector2D(myRb->GetVelocity().x, 0),speed.x);
}

