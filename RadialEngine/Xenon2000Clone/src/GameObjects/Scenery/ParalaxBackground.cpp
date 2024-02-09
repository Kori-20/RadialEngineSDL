#include "ParalaxBackground.h"

ParalaxBackground::ParalaxBackground(const std::string& path, float w, float h, int s, float speed, float yPos) : GameObject()
{
	paralLayerFront = &AddComponent<SpriteComponent>(path,w,h,s);
	parallaxSpeed = speed;
	transform->SetPosition(0, yPos);
	SetLayer(-9);
}

ParalaxBackground::ParalaxBackground()
{
	paralLayerFront = &AddComponent<SpriteComponent>("Assets/bck2.bmp", 1, 3, 2);
	transform->SetPosition(0, 600);
}

ParalaxBackground::~ParalaxBackground()
{
	
}

void ParalaxBackground::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	
	transform->SetPosition(transform->GetPosition().x, transform->GetPosition().y + deltaTime * parallaxSpeed);
	if (transform->GetPosition().y >= 3000)
	{
		transform->SetPosition(transform->GetPosition().x, -600);
	}
}
