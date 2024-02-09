//Animator Component only works if Sprite Component is present
#pragma once
#include "ECS/Component.h"
#include "SDLSpriteComponent.h"
#include <iostream>
#include <map>
#include <ostream>
#include <vector>

struct  SDLAnimation 
{
	int width, height;

	const char* name; 
	const char* path;

	int rows, columns = 1;

	int startFrameX, startFrameY = 1;
	int endFrameX = rows;
	int endFrameY = columns;
	int frameWidth = width / rows;
	int frameHeight = height / columns;

	bool loop = true;

	float playRate = 1.0f;

	//use to change animation direction //!!! switch to an enum latter if needed
	bool animPlayRight = true;

	SDLAnimation(const char* animName,const char* animPath,int animWidth,int animHeight):
		name(animName),path(animPath),width(animWidth),height(animHeight){}
};

class RE_API SDLAnimatorComponent : public Component
{
public:
	SDLAnimatorComponent() = default;

	bool Init() override;
	void Update(float deltaTime) override;
	void Draw(float deltaTime) override;

	void PlayAnimation(const char* animName);
	void AddAnimation(SDLAnimation anim);

	void SetSprite(SDLSpriteComponent* spriteComponent) { sprite = spriteComponent; }

protected:
	SDLSpriteComponent* sprite;
	SDLAnimation* currentAnim;

	std::map<const char*, SDLAnimation> animGroup;

	bool animPlaying = false;
	float frameTime;
};

