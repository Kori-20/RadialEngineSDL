#pragma once
#include <sdl2\SDL_render.h>

class SDLTextureManager
{
public:
	static struct SDL_Texture* LoadTexture(const char* texture);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Point center);
	static void DrawBackground(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Point center);
};

