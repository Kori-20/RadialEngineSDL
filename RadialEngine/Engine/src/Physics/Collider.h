#pragma once
#include "ECS/Component.h"
#include "Core/Core.h"
#include <box2d/b2_fixture.h>
#include "Aid/Transform.h"
#include <vector>

enum CollisionShape {
	BoxShape,
	CircleShape,
	CapsuleShape
};

enum CollisionFilter : short{
	StaticF = 0x1,
	GameObjectF = 0x2,
	PawnF = 0x3,
	PlayerF = 0x4,
	AllyF = 0x5,
	EnemyF = 0x6,
	ProjectileF = 0x7,
	AllyProjectileF = 0x8,
};

//Test and check masking
enum CollisionMasking {
	StaticMask = PlayerF | GameObjectF | ProjectileF,
	GameObjectMask = StaticF | PawnF | EnemyF | PlayerF,

	PawnMask = StaticF | GameObjectF | EnemyF,
	PlayerMask = StaticF | GameObjectF | EnemyF,
	AllyMask = StaticF | GameObjectF | EnemyF,

	EnemyMask = GameObjectF | PlayerF| AllyProjectileF,

	ProjectileMask = EnemyF | GameObjectF | PlayerF,
	AllyProjectileMask = EnemyF,

	MaskAll = -1,
	MaskNone = 0,
};

class RE_API Collider : public Component
{
public:
	Collider() = default;
	~Collider() override = default;

	virtual b2Fixture* CreateFixture() = 0;
	CollisionShape GetShape() const;
	Vector2D GetDimensions() const;

	CollisionFilter GetFilterCollision() const;
	void SetFilterCollision(CollisionFilter filter);

	CollisionMasking GetFilterMasking() const;
	void SetFilterMasking(CollisionMasking mask);

	void AddToIgnore(class GameObject* objectToIgnore);
	std::vector<class GameObject*> GetIgnoredObjects();

	//Change sensor to turn on Collision
	bool _sensor = true; // All objects by default are overlap only
	bool _enabled = true;

	Vector2D offset;

protected:
	CollisionFilter colFilter = StaticF;
	CollisionMasking colMask = MaskNone;
	CollisionShape colShape;
	Vector2D dimensions;

	std::vector<class GameObject*> objBlackList{};

};

