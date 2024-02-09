#include "SDLTextureManager.h"
#include "Window.h"
#include "sdl2\SDL_surface.h"
#include "SDLSpriteComponent.h"
#include <iostream>
#include <filesystem>
#include <Aid/Logger.h>
#include "sdl2\SDL_image.h"

SDL_Texture* SDLTextureManager::LoadTexture(const char* texture) {

	SDL_Surface* tmpSurface = IMG_Load(texture);

	if (!std::filesystem::exists(texture)) 
	{
		Logger::Issue("Invalid Text Path :: SDLTextureManager.16");
	}

	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 255, 0, 255));
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::GetRenderer(), tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}

void SDLTextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Point center) {
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	SDL_RenderCopyEx(Window::GetRenderer(), tex, &src, &dest, 0.0f, &center, SDL_FLIP_NONE);
}

void SDLTextureManager::DrawBackground(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Point center) {
	SDL_RenderCopy(Window::GetRenderer(), tex, NULL, NULL);
}
