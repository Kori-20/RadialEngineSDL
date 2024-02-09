#include "Collider.h"
#include <Aid/Logger.h>

CollisionShape Collider::GetShape() const
{
	return colShape;
}

Vector2D Collider::GetDimensions() const
{
	return dimensions;
}

CollisionFilter Collider::GetFilterCollision() const
{
	return colFilter;
}

void Collider::SetFilterCollision(CollisionFilter filter)
{
	colFilter = filter;
}

CollisionMasking Collider::GetFilterMasking() const
{
	return colMask;
}

void Collider::SetFilterMasking(CollisionMasking mask)
{
	colMask = mask;
}

void Collider::AddToIgnore(GameObject* objectToIgnore)
{
	objBlackList.push_back(objectToIgnore);
}

std::vector<class GameObject*> Collider::GetIgnoredObjects()
{
	return objBlackList;
}
