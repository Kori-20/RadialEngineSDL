#pragma once
#include <box2d/b2_world_callbacks.h>

class ContactListener : public b2ContactListener, public b2ContactFilter
{
public:
	ContactListener() = default;

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;//Solves filters and collisions between objects
};

