#pragma once
#include "Collider.h"
#include "Core/Core.h"

class RE_API BoxCollision : public Collider {

public:
	BoxCollision();
	BoxCollision(Vector2D boxDimenssions);

	b2Fixture* CreateFixture() override;

	void SetBoxDimenssions(Vector2D box);
};








