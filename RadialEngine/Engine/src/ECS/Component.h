#pragma once
#include "Core/Core.h"

class RE_API Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	virtual void SetOwner(class Entity* newOwner) { owner = newOwner; }
	class Entity* GetOwner() const { return owner; }

	virtual bool Init() { return true; }
	virtual void Start() {}
	virtual void Draw(float deltaTime) {}
	virtual void Update(float deltaTime) {}
	virtual void OnDestroyed() {}

protected:
	class Entity* owner;
};

