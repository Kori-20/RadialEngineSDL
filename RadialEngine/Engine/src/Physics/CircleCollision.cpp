#include "CircleCollision.h"

CircleCollision::CircleCollision()
{
	colShape = CircleShape;
}

CircleCollision::CircleCollision(float radius)
{
	colShape = CircleShape;

}

b2Fixture* CircleCollision::CreateFixture()
{
	return nullptr;
}

void CircleCollision::SetRadius(float radius)
{

}
