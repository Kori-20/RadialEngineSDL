#pragma once
#include <array>

#include "ECS/Component.h"
#include "Core/Core.h"
#include "ECS/Component.h"
#include "Aid/Transform.h"
#include "Render/TextureManager.h"
#include <string>

class RE_API SpriteComponent : public Component
{
    friend class AnimatorComponent;

   public:
    SpriteComponent(const std::string& path, float spriteWidht, float spriteHeight, Vector2D sScale);
    SpriteComponent(const std::string& path, float spriteWidht, float spriteHeight, float scaleX, float scaleY);
    SpriteComponent(const std::string& path, float spriteWidht, float spriteHeight, float rawScale);//Ease of use

    ~SpriteComponent();

    bool Init() override;
    void Draw(float deltaTime) override;

    void SetSpritePath(const std::string& path);
    void SetSpriteRenderSize(const Vector2D& size);

    void SetSpriteTransform(Transform* transform) { spriteTransform = transform; }
    Transform* GetSpriteTransform() { return spriteTransform; }
    int numberOfRows = 1;
    int numberOfCollums = 1;

    std::array<Vector2D, 4> UVs;

    bool isAnimated = false;
private:
    Transform* spriteTransform;
    int spriteTextureID;
    std::string spritePath;
    Vector2D spriteRenderSize;
 
    Vector2D spriteScale;
};

