#pragma once
#include "Aid/Transform.h"

struct b2BodyDef;

class PhysicsWorld
{
public:
	//Singleton
	static PhysicsWorld* GetInstance() { return world = (world != nullptr) ? world : new PhysicsWorld(); }

	bool Init();
	void Update(float deltaTime);
	void DebugDraw(float deltaTime);


	class b2Body* RegisterBody(b2BodyDef& bodyDef);
	class b2World* b2dWorld;

	Vector2D gravityForce;

protected:
	PhysicsWorld();
	~PhysicsWorld();

	static inline PhysicsWorld* world = nullptr;

	class ContactListener* contactListener;
};

