#pragma once
#include "GameObject.h"
#include "Input\Controller.h"
#include "Input\InputHandler.h"
#include <Physics/RigidBody.h>

class RE_API Pawn : public GameObject
{
public:

	Pawn();
	~Pawn();

	//Temporary Input system
	virtual void Update(float deltaTime) override;

protected:
	Controller* pawnController;

public:
	Controller* GetController() { return pawnController; }
};

