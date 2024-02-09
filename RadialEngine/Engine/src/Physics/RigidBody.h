#pragma once
#include "Core/Core.h"
#include "Aid/Transform.h"
#include "ECS/Component.h"

class b2Fixture;
struct b2FixtureDef;

enum EBodyType {
	DynamicB,// Fully simulated and respond to forces and collisions
	KinematicB,// Constant velocity and can be moved manually.
	StaticB, // Do not move or change position over time
};

class RE_API RigidBody : public Component
{
public:
	RigidBody() = default;
	RigidBody(EBodyType newBody, float newMass);
	RigidBody(EBodyType newBody, float newMass, class Collider* newCollider);

	bool Init() override;
	void Start() override;
	void Update(float deltaTime) override;

	void SetVelocity(Vector2D newVelocity);
	inline Vector2D GetVelocity() { return velocity; }

	void Move(Vector2D direction, float speed);

	inline EBodyType GetBodyType() { return bodyType; }

	void SetCountinuous(bool value);

	void CreateBaseFixture();
	void CreateFixture();

	void SetCollider(class Collider* newCollider);

	void SetMass(float newMass) { mass = newMass; }

	b2FixtureDef* fixture;
	class b2Fixture* ownerFixture;
	class b2BodyDef* bodyDef;

	EBodyType bodyType = DynamicB;

	class b2Body* GetBody();

	float mass = 1.f;
	float gravityScale = 1.f;
	float linearDamping = 0.f;
	float angularDamping = 0.f;
	float _density = 2.f;
	float _friction = 0.2f;

	bool isAwake = true;
	bool _allowSleep = false;
	bool _isBullet = false;//b2_body base defenition, bullet is used for fast moving objects by using continuous collision detection
	bool fixedRotation = false;
	bool afectedByGravity = true;

protected:
	void SetBodyType(EBodyType newBodyType);

	class Transform* transform;
	class b2Body* body;
	Vector2D velocity;
	Vector2D position;
	
	class Collider* collider;
};

