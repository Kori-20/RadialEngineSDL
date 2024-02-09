#include "RigidBody.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "Aid/Logger.h"
#include "Aid/Transform.h"
#include "ECS/Entity.h"
#include "Collider.h"
#include "PhysicsWorld.h"
#include <ECS/GameObject.h>

RigidBody::RigidBody(EBodyType newBody, float newMass)
{
	bodyType = newBody;
	mass = newMass;
}

RigidBody::RigidBody(EBodyType newBody, float newMass, Collider* newCollider)
{
	bodyType = newBody;
	mass = newMass;
	collider = newCollider;
}

bool RigidBody::Init()
{
	auto a = ((GameObject*)(GetOwner()));
	transform = a->GetTransform();

	//Setting box2D body properties
	bodyDef = new b2BodyDef();
	bodyDef->userData.pointer = reinterpret_cast<uintptr_t>(this);//sets the bodyDef's user data to the address of this rigidbody

	SetBodyType(bodyType);

	//Setting box2D body properties
	bodyDef->gravityScale = 980.0f;
	bodyDef->awake = true;
	bodyDef->allowSleep = _allowSleep;
	bodyDef->enabled = true;

	Vector2D rbPosition = transform->GetPosition();

	bodyDef->position = b2Vec2(rbPosition.x, rbPosition.y);
	bodyDef->bullet = _isBullet;

	b2BodyUserData bodyData;
	bodyData.pointer = reinterpret_cast<uintptr_t>(this);
	bodyDef->userData = bodyData;

	//Create the body in the physics world
	body = PhysicsWorld::GetInstance()->RegisterBody(*bodyDef);
	fixture = new b2FixtureDef();

	if (collider == nullptr)
	{
		CreateBaseFixture();
		Logger::Warning("No collider attached to rigidbody, creating default box collider");
	}
	else
	{
		CreateFixture();
	}

	ownerFixture = body->CreateFixture(fixture);
	gravityScale = afectedByGravity ? 980 : 0; // true = 980, false = 0
	body->SetGravityScale(gravityScale);

	return false;
}

void RigidBody::Start()
{

}

void RigidBody::Update(float deltaTime)
{
	Component::Update(deltaTime);

	if (afectedByGravity) {
		body->SetGravityScale(-gravityScale);
	}
	else 
	{
		body->SetGravityScale(0);
	}

	const b2Vec2& b2Vec = body->GetPosition();
	transform->SetPosition(Vector2D(b2Vec.x, b2Vec.y));//updates transform position to match box2D body position
}

void RigidBody::SetVelocity(Vector2D newVelocity)
{
	velocity = newVelocity;

	b2Vec2 vecVelocity;
	vecVelocity.x = velocity.x;
	vecVelocity.y = velocity.y;

	body->SetLinearVelocity(vecVelocity); //sets the velocity of the body to the new velocity
}

void RigidBody::Move(Vector2D direction, float speed)
{
	SetVelocity(direction.Normalize() * speed);
}

void RigidBody::SetBodyType(EBodyType newBodyType)
{
	switch (newBodyType)
	{
	case DynamicB:
	default:
		bodyDef->type = b2_dynamicBody;
		break;
	case KinematicB:
		bodyDef->type = b2_kinematicBody;
		break;
	case StaticB:
		bodyDef->type = b2_staticBody;
		break;
	}
}

void RigidBody::SetCountinuous(bool value)
{
	//def->bullet = value;
}

void RigidBody::CreateBaseFixture()
{
	fixture->userData.pointer = reinterpret_cast<uintptr_t>(this);
	fixture->isSensor = true;
	fixture->friction = _friction;
	fixture->density = _density;

	fixture->filter.categoryBits = StaticF;
	fixture->filter.maskBits = MaskNone;

	//Create a basic box collider
	auto dynamicBox = new b2PolygonShape();
	dynamicBox->SetAsBox(1.0f, 1.0f);
	fixture->shape = dynamicBox;
}

void RigidBody::CreateFixture()
{
	fixture->userData.pointer = reinterpret_cast<uintptr_t>(collider);
	fixture->isSensor = collider->_sensor;
	fixture->friction = _friction;
	fixture->density = _density;

	fixture->filter.categoryBits = collider->GetFilterCollision();
	fixture->filter.maskBits = collider->GetFilterMasking();

	switch (collider->GetShape()) {
	case BoxShape: {
		const auto newBox = new b2PolygonShape();
		fixture->shape = newBox;
		b2Vec2 positionOffset(collider->offset.x, collider->offset.y);
		newBox->SetAsBox(collider->GetDimensions().x, collider->GetDimensions().y, positionOffset, 0);

		break;
	}
	case CircleShape:
	default: {
		const auto newCircle = new b2CircleShape();
		newCircle->m_radius = collider->GetDimensions().x;
		fixture->shape = newCircle;
	}
	}
}


//TODO:: Add a way to allow for multiple colliders to exist in 1 body so that overlapping and collision can be handled
void RigidBody::SetCollider(Collider* newCollider)
{
	collider = newCollider;
}

b2Body* RigidBody::GetBody()
{
	return body;
}
