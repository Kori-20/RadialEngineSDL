#pragma once
#include "ECS/Component.h"
#include "Core/Core.h"
#include "SpriteComponent.h"

class RE_API AnimatorComponent : public Component
{
public:
    AnimatorComponent(SpriteComponent* spriteComponent) : m_pSpriteComponent(spriteComponent) {}
    ~AnimatorComponent() = default;

    void Draw(float deltaTime) override;
    void SetAnimParameters(int startRow, int endRow, float speed, bool animPlay);
        

    int animStartRow =1;
    int animEndRow=5;
    bool playForward = true;
    int numberOfRows;
    int numberOfCollums;
    float totalElapsedTime = 0.0f;
    float playRate;
    bool animPlay;

private:
    SpriteComponent* m_pSpriteComponent;
    
};

