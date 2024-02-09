#include "SDLAnimatorComponent.h"
#include "ECS/Entity.h""
#include "Aid/Transform.h"
#include <cassert>
#include <string>

bool SDLAnimatorComponent::Init()
{
	Component::Init();

	sprite = &GetOwner()->GetComponent<SDLSpriteComponent>();
	assert(sprite != nullptr); // Breaks program and outpus error and line location

	return true;
}

void SDLAnimatorComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);
}

void SDLAnimatorComponent::Draw(float deltaTime)
{
	Component::Draw(deltaTime);

	if (frameTime >= 1.f / currentAnim->playRate)
	{
		//Animation direction
		if (currentAnim->animPlayRight) {
			sprite->srcRect.x += sprite->srcRect.w;
		}
		else {
			sprite->srcRect.x -= sprite->srcRect.w;
		}

		//Animation loop 
		if (sprite->srcRect.x == currentAnim->endFrameX * currentAnim->frameWidth) {

			if (currentAnim->loop) {
				sprite->srcRect.x = currentAnim->startFrameX;
			}
			else {
				if (sprite->srcRect.y - sprite-> srcRect.h < currentAnim-> endFrameY * currentAnim->frameHeight)
				{
					sprite->srcRect.x = currentAnim->startFrameX;
				}
				else
				{
					sprite->srcRect.x = currentAnim->endFrameX * currentAnim->frameWidth + sprite->srcRect.w;
				}
			}
			sprite->srcRect.y += sprite->srcRect.h;

			if (sprite->srcRect.y >= currentAnim->endFrameY * currentAnim->frameHeight)
			{
				if (currentAnim->loop) {
					sprite->srcRect.y = currentAnim->startFrameY;
				}
				else {
					sprite->srcRect.y = currentAnim->endFrameY * currentAnim->frameHeight - sprite->srcRect.h;
					animPlaying = false;
				}
			}
		}
		frameTime = 0;
	}
}

void SDLAnimatorComponent::PlayAnimation(const char* animName)
{
	if (animGroup.contains(animName)) 
	{
		if(currentAnim == &animGroup.at(animName))
		{
			return; // Already playing this animation
		}
		{
			currentAnim = &animGroup.at(animName);
			sprite->SetTexture(currentAnim->path);
			animPlaying = true;
			currentAnim->frameWidth = (currentAnim->width / currentAnim->rows);
			currentAnim->frameHeight = (currentAnim->height / currentAnim->columns);
			sprite->SetNewSize(currentAnim->frameWidth, currentAnim->frameHeight);
			sprite->srcRect.x = currentAnim->startFrameX * currentAnim->startFrameY;
		}
	}
}

void SDLAnimatorComponent::AddAnimation(SDLAnimation anim)
{

}

