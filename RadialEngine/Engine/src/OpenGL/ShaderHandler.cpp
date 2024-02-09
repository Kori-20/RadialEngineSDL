#include "ShaderHandler.h"

const char* vertexSource = R"glsl(
#version 460 core
	
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoords;
layout (location = 3) in float textureIndex;

out vec3 Color;
out vec2 TextureCoords;
out float TextureIndex;
	
void main()
{
	gl_Position = vec4(position, 1.0);
	Color = color;
	TextureCoords = textureCoords;
	TextureIndex = textureIndex;
}
)glsl";

const char* fragmentSource = R"glsl(
#version 460 core

in vec3 Color;
in vec2 TextureCoords;
in float TextureIndex;
uniform sampler2D Textures[32];

out vec4 outColor;

void main()
{
	int index = int(TextureIndex);
	outColor = texture(Textures[index], TextureCoords);
			
}
)glsl";

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Vertex Shader 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	//Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	//Shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	//Clean shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Enable blend for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Activate();
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}
