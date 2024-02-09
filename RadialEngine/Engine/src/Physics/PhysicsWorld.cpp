#include "PhysicsWorld.h"
#include "Aid/Logger.h"
#include "ContactListener.h"
#include "box2d/b2_world.h"

bool PhysicsWorld::Init()
{
	Logger::Info("PhysicsWorld Initialized");
	return true;
}

void PhysicsWorld::Update(float deltaTime)
{
	b2dWorld->Step(deltaTime, 8, 4);
	// 6 velocity iterations and 4 position iterations
}

void PhysicsWorld::DebugDraw(float deltaTime)
{
	b2dWorld->DebugDraw();
}

b2Body* PhysicsWorld::RegisterBody(b2BodyDef& bodyDef)
{
	return b2dWorld->CreateBody(&bodyDef);
}

PhysicsWorld::PhysicsWorld()
{
	gravityForce = Vector2D(0, -9.8f);
	b2dWorld = new b2World(b2Vec2(gravityForce.x, gravityForce.y));
	contactListener = new ContactListener();
	b2dWorld->SetContactListener(contactListener);
	b2dWorld->SetContactFilter(contactListener);
}

PhysicsWorld::~PhysicsWorld()
{

}