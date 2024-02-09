#include "BackgroundSprite.h"

BackgroundSprite::BackgroundSprite() : GameObject()
{
	bckgSprite = &AddComponent<SpriteComponent>("Assets/galaxy2.bmp", 1, 1, 2);
	transform->SetPosition(0, 600);
	SetLayer(-10);
}

BackgroundSprite::~BackgroundSprite()
{

}

