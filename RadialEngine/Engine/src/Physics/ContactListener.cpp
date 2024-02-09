#include "ContactListener.h"
#include "Collider.h"
#include "ECS/GameObject.h"
#include "box2d/b2_contact.h"

class b2Contact;

void ContactListener::BeginContact(b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);

	const auto colliderA = reinterpret_cast<Collider*>(contact->GetFixtureA()->GetUserData().pointer);
	const auto colliderB = reinterpret_cast<Collider*>(contact->GetFixtureB()->GetUserData().pointer);

	const auto objectOwnerA = dynamic_cast<GameObject*>(colliderA->GetOwner());
	const auto objectOwnerB = dynamic_cast<GameObject*>(colliderB->GetOwner());

	if (colliderA != nullptr && colliderB != nullptr)
	{
		if (!colliderA->_sensor && !colliderB->_sensor) {
			objectOwnerA->OnCollisionStart(objectOwnerB);
			objectOwnerB->OnCollisionStart(objectOwnerA);
		}

		if (colliderA->_sensor) {
			objectOwnerA->OnOverlapBegin(objectOwnerB);
		}

		if (colliderB->_sensor) {
			objectOwnerB->OnOverlapBegin(objectOwnerA);
		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	b2ContactListener::EndContact(contact);
	/*
	const auto colliderA = reinterpret_cast<Collider*>(contact->GetFixtureA()->GetUserData().pointer);
	const auto colliderB = reinterpret_cast<Collider*>(contact->GetFixtureB()->GetUserData().pointer);

	bool isCollisionEnabled = (contact->GetFixtureA()->GetFilterData().maskBits &
		contact->GetFixtureA()->GetFilterData().categoryBits) != 0;

	if (isCollisionEnabled) 
	{
		if (colliderA != nullptr && colliderB != nullptr) 
		{
			GameObject* const objectOwnerA = dynamic_cast<GameObject*>(colliderA->GetOwner());
			GameObject* const objectOwnerB = dynamic_cast<GameObject*>(colliderB->GetOwner());

			objectOwnerA->OnCollisionEnd(objectOwnerB);
			objectOwnerB->OnCollisionEnd(objectOwnerA);
		}
	}
	*/
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	b2ContactListener::PostSolve(contact, impulse);
	//Add utility
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2ContactListener::PreSolve(contact, oldManifold);
	//Add utility
}

bool ContactListener::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	const b2Filter& filterA = fixtureA->GetFilterData();
	const b2Filter& filterB = fixtureB->GetFilterData();

	auto ColA = reinterpret_cast<Collider*>(fixtureA->GetUserData().pointer);
	auto ColB = reinterpret_cast<Collider*>(fixtureB->GetUserData().pointer);

	for (const auto element : ColA->GetIgnoredObjects()) {
		if (ColB->GetOwner() == element) {
			return false;
		}
	}
	for (const auto element : ColB->GetIgnoredObjects()) {
		if (ColA->GetOwner() == element) {
			return false;
		}
	}

	const bool collideA = (filterA.maskBits & filterB.categoryBits) != 0;
	const bool collideB = (filterA.categoryBits & filterB.maskBits) != 0;
	const bool collidC = ColA->_enabled;
	const bool collidD = ColB->_enabled;
	const bool collide = collideA && collideB && collidC && collidD;

	return collide;
}
