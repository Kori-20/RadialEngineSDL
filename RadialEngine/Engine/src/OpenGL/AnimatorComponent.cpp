#include "AnimatorComponent.h"
#include "Render/Renderer.h"

void AnimatorComponent::Draw(float deltaTime) {
    Component::Draw(deltaTime);

    if (m_pSpriteComponent && m_pSpriteComponent->isAnimated) {
        const float spriteWidth = 1.f / numberOfCollums;
        const float spriteHeight = 1.f / numberOfRows;

        const int total_frames = (animEndRow - animStartRow + 1) * numberOfCollums;

        totalElapsedTime += deltaTime;
        int currentFrame;
        if (animPlay)
        {
            currentFrame = static_cast<int>((totalElapsedTime / playRate) * total_frames) % total_frames;
        }
        else
        {
            currentFrame = total_frames - static_cast<int>((totalElapsedTime / playRate) * total_frames) - 1;
        }

        bool animationComplete = (currentFrame >= total_frames);

        // If the animation is complete, reset to the starting frame
        if (animationComplete)
        {
            currentFrame = animStartRow * numberOfCollums; // Reset to the starting frame
        }

        // Calculate the row and column of the current frame
        int currentRow = currentFrame / numberOfCollums;
        int currentColumn = currentFrame % numberOfCollums;

        // Calculate UV coordinates for the current frame
        float u0 = currentColumn * spriteWidth;
        float v0 = 1.0f - ((currentRow + animStartRow) * spriteHeight);
        if (currentRow == (animEndRow - animStartRow) && currentRow != animStartRow)
        {
            v0 += spriteHeight;
        }
        float u1 = u0 + spriteWidth;
        float v1 = v0 + spriteHeight;

        // Update UVs for the sprite component
        std::array<Vector2D, 4> UVs = std::array<Vector2D, 4>{
            {Vector2D(u0, v0), Vector2D(u1, v0), Vector2D(u1, v1), Vector2D(u0, v1)}
        };
        m_pSpriteComponent->UVs = UVs;
    }
}

void AnimatorComponent::SetAnimParameters(int startRow, int endRow, float speed, bool animPlay) {
    animStartRow = startRow;
    animEndRow = endRow;
    playRate = speed;
    this->animPlay = animPlay;
}