#pragma once
#include "Core/Core.h"

class RE_API TextureManager {
public:
    static int LoadOpenGlTexture(const char* path, bool flipHorizontal);
};
