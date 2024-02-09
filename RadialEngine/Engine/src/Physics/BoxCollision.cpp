#include "BoxCollision.h"
#include "RigidBody.h"
#include "ECS/Entity.h"
#include "box2d/b2_polygon_shape.h"


BoxCollision::BoxCollision()
{
	colShape = BoxShape;
}

BoxCollision::BoxCollision(Vector2D boxDimenssions)
{
	colShape = BoxShape;
	SetBoxDimenssions(boxDimenssions);
}

b2Fixture* BoxCollision::CreateFixture()
{
	RigidBody* rb = &GetOwner()->GetComponent<RigidBody>();
	assert(rb != nullptr);

	const auto fixture = new b2FixtureDef();
	fixture->userData.pointer = reinterpret_cast<uintptr_t>(this);
	fixture->isSensor = _sensor;
	fixture->friction = rb->_friction;
	fixture->density = rb->_density;

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(dimensions.x, dimensions.y);
	fixture->shape = &dynamicBox;

	return rb->GetBody()->CreateFixture(fixture);


}

void BoxCollision::SetBoxDimenssions(Vector2D boxDimenssions)
{
	dimensions.x = boxDimenssions.x;
	dimensions.y = boxDimenssions.y;
}
