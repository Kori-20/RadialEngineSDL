// SpriteComponent.cpp
#include "SpriteComponent.h"
#include "Render/Renderer.h"
#include "ECS/Entity.h"
#include "Aid/Logger.h"
#include <ECS/GameObject.h>

SpriteComponent::SpriteComponent(const std::string& path, float spriteWidht, float spriteHeight, Vector2D sScale)
{
	SetSpritePath(path);
	spriteScale = sScale;
	SetSpriteRenderSize(Vector2D(spriteWidht, spriteHeight));
}

SpriteComponent::SpriteComponent(const std::string& path, float spriteWidht, float spriteHeight, float scaleX, float scaleY)
{
	SetSpritePath(path);
	spriteScale.x = scaleX;
	spriteScale.y = scaleY;
	SetSpriteRenderSize(Vector2D(spriteWidht, spriteHeight));
}

SpriteComponent::SpriteComponent(const std::string& path, float spriteWidht, float spriteHeight, float rawScale)
{
	SetSpritePath(path);
	spriteScale.x = spriteScale.y = rawScale;
	SetSpriteRenderSize(Vector2D(spriteWidht, spriteHeight));
}

SpriteComponent::~SpriteComponent() {}

bool SpriteComponent::Init()
{
	auto a = ((GameObject*)(GetOwner()));
	spriteTransform = a->GetTransform();

	if (!spriteTransform)
	{
		return false;
	}

	if (!spritePath.empty())
	{
		spriteTextureID = TextureManager::LoadOpenGlTexture(spritePath.c_str(), false);//Load the texture
	}

	return true;
}

void SpriteComponent::Draw(float deltaTime)
{
	Component::Draw(deltaTime);

	const float spriteWidth = 1.f / numberOfRows;
	const float spriteHeight = 1.f / numberOfCollums;

	if (spriteTextureID != 0)
	{
		auto xpos = spriteTransform->GetPosition().x;
		auto ypos = spriteTransform->GetPosition().y;


		if (!isAnimated) //On Sprite sheets will select the 1st frame
		{
			UVs = std::array<Vector2D, 4>{
				{Vector2D(0.0f, 0.0f), Vector2D(spriteWidth, 0.0f), Vector2D(spriteWidth, spriteHeight), Vector2D(0.0f, spriteHeight)}};
		}

		//Send image to render
		Renderer::CheckQuads({ xpos,ypos }, { spriteScale.x,spriteScale.y }, spriteTextureID, spriteRenderSize, UVs);
	}
}

void SpriteComponent::SetSpritePath(const std::string& path)
{
	spritePath = path;
}

void SpriteComponent::SetSpriteRenderSize(const Vector2D& size)
{
	spriteRenderSize = size;
}
