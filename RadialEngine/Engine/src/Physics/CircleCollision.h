#pragma once
#include "Collider.h"
#include "Core/Core.h"

//INCOMPLETE CLASS

class RE_API CircleCollision : public Collider
{
public:
	CircleCollision();
	CircleCollision(float radius);

	b2Fixture* CreateFixture() override;

	void SetRadius(float radius);
	
};

