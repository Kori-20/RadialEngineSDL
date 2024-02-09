#pragma once
#include <sdl2\SDL_rect.h>
#include <sdl2\SDL_render.h>
#include "ECS/Component.h"

class Transform;

class RE_API SDLSpriteComponent : public Component
{
	friend class SDLAnimatorComponent;

public:
	SDLSpriteComponent() = default;
	SDLSpriteComponent(const char* path);
	SDLSpriteComponent(const char* path, int width, int height, int scale);
	SDLSpriteComponent(const char* path, int width, int height, int scale, int layer);
	~SDLSpriteComponent() override;

	bool Init() override;
	void Start() {}
	void Draw(float deltaTime) override;
	void Update(float deltaTime) override;
	void SetTexture(const char* path); //used mostly by animation or to cause drastic sprite changes

	void OnDestroyed() {}
	
protected:
	const char* spritePath;//ex.: "assets/texture.png"
	SDL_Rect srcRect, destRect;//source and destination rectangles
	Transform* transform;
	SDL_Texture* texture;//texture to be rendered to the screen
	SDL_Point centerPoint;

	bool isBackground = false;
	int spriteWidth, spriteHeight = 32;//default to 32x32
	float spriteScale = 1.0f;

	//layering system still requires rendering fucntionality
	int spritelayer = 0;

public:

	void SetAsBackground(bool value) { isBackground = value; }
	void SetNewSize(int newWidth, int newHeight) { spriteWidth = newWidth; spriteHeight = newHeight; }
	void SetSpritePosition(int x, int y);
	void SetScale(float newScale) { spriteScale = newScale; }
	void SetLayer(int newLayer) { spritelayer = newLayer; }
};

