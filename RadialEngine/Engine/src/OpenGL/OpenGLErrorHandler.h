#pragma once
#include <iostream>
#include <string>
#include "Aid/Logger.h"
#include <glad/glad.h>


class OpenGLErrorHandler
{
public:
	static void ErrorCheck() 
	{
		GLenum error = glad_glGetError();

		while (error != GL_NO_ERROR) 
		{
			std::string stringerror;
			switch (error) {
			case GL_INVALID_OPERATION: stringerror = "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_ENUM: stringerror = "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE: stringerror = "GL_INVALID_VALUE";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: stringerror = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			case GL_INVALID_INDEX: stringerror = "GL_INVALID_INDEX";
				break;
			default: stringerror = std::to_string(error);
			}
			Logger::Issue("OpenGL Error: " + stringerror);

			error = glGetError();
		}
	}
};

