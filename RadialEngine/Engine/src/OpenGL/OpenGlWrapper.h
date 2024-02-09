#pragma once
#include "sdl2/SDL.h"

class OpenGlWrapper
{
public:
	static void Init();//Configures OpenGl using SDL
	static SDL_GLContext ConfigureOpenGl(struct SDL_Window* window);
};

