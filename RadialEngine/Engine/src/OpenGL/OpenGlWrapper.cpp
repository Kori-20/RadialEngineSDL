#include "OpenGlWrapper.h"
#include <glad/glad.h>
#include "Aid/Logger.h"

void OpenGlWrapper::Init()
{
	//Initialize glad
	if (!gladLoadGL())
	{
		Logger::Issue("Glad failed to initialize");
	}

	Logger::Note("Glad initialized");

	//Get OpenGL version
	const GLubyte* glVersion = glGetString(GL_VERSION);
	if (glVersion)
	{
		Logger::Display("OpenGL Version: " + std::string(reinterpret_cast<const char*>(glVersion)));
	}
	else
	{
		Logger::Issue("Failed to retrieve OpenGL version");
	}

	//OpenGl confugiration using SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
}

SDL_GLContext OpenGlWrapper::ConfigureOpenGl(SDL_Window* window)
{
	//Create OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!context)
	{
		Logger::Issue("Failed to create OpenGL context");
	}

	//Load OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		Logger::Issue("Glad failed to initialize");
	}

	Logger::Note("OpenGL initialized");
	return context;
}
