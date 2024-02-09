#include "Pawn.h"
#include "Core/EngineCore.h"

Pawn::Pawn() : GameObject()
{
	pawnController = &AddComponent<Controller>();
	//InputHandler::getInstance()->pawn = this;
}

Pawn::~Pawn()
{
	
}

void Pawn::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}
