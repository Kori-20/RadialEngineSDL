#include "SDLSpriteComponent.h"
#include "SDLTextureManager.h"
#include "Aid\Transform.h"
#include "ECS\Component.h"
#include "ECS\Entity.h"
#include <sdl2\SDL.h>
#include "ECS\GameObject.h"
#include "Aid/Logger.h"


SDLSpriteComponent::SDLSpriteComponent(const char* path)
{
	spritePath = path;
}

SDLSpriteComponent::SDLSpriteComponent(const char* path, int width, int height, int scale)
{
	spritePath = path;
	spriteWidth = width;
	spriteHeight = height;
	spriteScale = scale;
}

SDLSpriteComponent::SDLSpriteComponent(const char* path, int width, int height, int scale, int layer)
{
	spritePath = path;
	spriteWidth = width;
	spriteHeight = height;
	spriteScale = scale;
	spritelayer = layer;
}

SDLSpriteComponent::~SDLSpriteComponent()
{
	SDL_DestroyTexture(texture);
}

bool SDLSpriteComponent::Init()
{
	if (spritePath) {
		texture = SDLTextureManager::LoadTexture(spritePath);

		auto a = ((GameObject*)(GetOwner()));
		transform = a->GetTransform();
	}
	if (!transform) 
	{
		return false;
	}

	srcRect.x = srcRect.y = 0;

	srcRect.w = spriteWidth;
	srcRect.h = spriteHeight;

	destRect.w = static_cast<int>(transform->GetPosition().x) - srcRect.w;
	destRect.h = static_cast<int>(transform->GetPosition().y) - srcRect.h;

	return true;
}

void SDLSpriteComponent::Draw(float deltaTime)
{
	Component::Draw(deltaTime);
	if (isBackground)
	{
		SDLTextureManager::DrawBackground(texture, SDL_Rect{}, SDL_Rect{}, SDL_Point{});
		return;
	}

	SDLTextureManager::Draw(texture, srcRect, destRect, centerPoint);
}

void SDLSpriteComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	destRect.x = static_cast<int>(transform->GetPosition().x);
	destRect.y = static_cast<int>(transform->GetPosition().y);
	destRect.w = spriteWidth * spriteScale;//sdl scale is int
	destRect.h = spriteHeight * spriteScale;//sdl scale is int

	srcRect.w = spriteWidth;
	srcRect.h = spriteHeight;

	centerPoint.x = transform->GetPosition().x;
	centerPoint.y = transform->GetPosition().y;
}

void SDLSpriteComponent::SetTexture(const char* path)
{
	if (strlen(path) != 0)
	{
		this->spritePath = path;
		texture = SDLTextureManager::LoadTexture(spritePath);
	}
}

void SDLSpriteComponent::SetSpritePosition(int x, int y)
{
	transform->SetPosition(x, y);
}
