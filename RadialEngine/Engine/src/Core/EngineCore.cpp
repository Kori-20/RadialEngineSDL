#include <memory>
#include <iostream>
#include "EngineCore.h"
#include <sdl2/SDL.h>

#include "Input/Controller.h"
#include "Level/LevelManager.h"
#include "Physics/PhysicsWorld.h"
#include "OpenGL/OpenGlWrapper.h"
#include "OpenGL/ShaderHandler.h"
#include "Render/Renderer.h"
#include "UserInterface/Font.h"
#include "UserInterface/TextUI.h"

//TODO: Make window size and title configurable game side

//Static variables
float EngineCore::m_deltaTime = 0.0f;
EngineCore* EngineCore::m_engine = nullptr;
SDL_Event EngineCore::_sdlEvent;

EngineCore::EngineCore()
{

}

void EngineCore::Initialize()
{
	Logger::Info("Engine initializing...");
	/******************************************************************/
	gameWindow = new Window("Xenon2000Clone", 800, 600, false);
	/******************************************************************/

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		SDL_Quit();
		return;
	}

	const std::string shaderPath = "OpenGL/";
	const Shader shaderProgram((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str());

	TextUI::GetInstance()->GetFontHandle()->SetFont("Assets/PNG/font16x16.png");
	// Gets ID of uniform called "scale"
	const GLuint textureUniformLocation = glGetUniformLocation(shaderProgram.ID, "Textures");

	int samplers[32];

	/* sizeof returns value in bytes, we must divide it by the size of the data type it
	*  contains to find out how many element an array has */
	for (int i = 0; i < sizeof(samplers) / sizeof(int); i++)
	{
		samplers[i] = i;
	}
	glUniform1iv(textureUniformLocation, 32, samplers);

	Renderer::Init(gameWindow->GetWindowSize());
	/******************************************************************/
	glClearColor(1.f, 0.63f, 1.f, 1.0f);

	//TextUI Text = new TextUI();
	LevelManager::getInstance().GetCurrentLevel()->OpenLevel();
	LevelManager::getInstance().GetCurrentLevel()->Init(); //Requires Level to be open
	/******************************************************************/
	Logger::Note("Engine initialized");
}

void EngineCore::Start()
{
	Logger::Info("Engine starting...");
	/******************************************************************/

	bool isRunning = true;

	//Frame rate
	lockFPS = 1000 / maxFPS;
	m_TicksCount = SDL_GetTicks();

	//Level setup
	LevelManager::getInstance().GetCurrentLevel()->Start();

	/******************************************************************/
	Logger::Note("Engine started");
}

void EngineCore::EventHandler()
{
	while (SDL_PollEvent(&_sdlEvent) != 0)
	{
		if (_sdlEvent.type == SDL_KEYDOWN)
		{
			InputHandler::GetInstance()->Press(_sdlEvent);
			//Logger::Warning("Key pressed");
		}
		else if (_sdlEvent.type == SDL_KEYUP)
		{
			InputHandler::GetInstance()->Release(_sdlEvent);
			//InputHandler::getInstance()->Release(_sdlEvent);
		}
		else if (_sdlEvent.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}
}

void EngineCore::Update()
{
	//Frame rate
	Uint64 currentTicks = SDL_GetPerformanceCounter();
	m_deltaTime = static_cast<float>(currentTicks - m_TicksCount) / SDL_GetPerformanceFrequency();
	m_TicksCount = currentTicks;
	targetDeltaTime = 1.0f / static_cast<float>(maxFPS);// Limit frame rate
	/******************************************************************/
	//Update game logic
	PhysicsWorld::GetInstance()->Update(targetDeltaTime);
	LevelManager::getInstance().GetCurrentLevel()->Update(m_deltaTime);
	LevelManager::getInstance().GetCurrentLevel()->LateUpdate(m_deltaTime);

	gameWindow->UpdateWindow(m_deltaTime);
	/******************************************************************/
	if (m_deltaTime < targetDeltaTime)//Frame rate lock (if frame rate is too fast, delay the frame)
	{
		SDL_Delay(static_cast<Uint32>((targetDeltaTime - m_deltaTime) * 1000));
		currentTicks = SDL_GetPerformanceCounter(); // Update currentTicks after the delay
		m_deltaTime = static_cast<float>(currentTicks - m_TicksCount) / SDL_GetPerformanceFrequency();
		m_TicksCount = currentTicks;
	}
	/******************************************************************/
	DisplayFPS();
}

void EngineCore::Draw()
{
	PhysicsWorld::GetInstance()->DebugDraw(targetDeltaTime);

	//OpenGl rendering logic
	glClear(GL_COLOR_BUFFER_BIT);
	Renderer::RenderStart();
	LevelManager::getInstance().GetCurrentLevel()->Draw(targetDeltaTime);

	
	TextUI::GetInstance()->PrintSreen(std::to_string(roundedFPS), 765, 600, Vector2D(.4f, .4f), 700);

	Renderer::RenderEnd();
	Renderer::CleanBinds();
	glClearColor(1.f, 0.f, 1.f, 0.0f);
	SDL_GL_SwapWindow(gameWindow->GetWindow());
}

void EngineCore::Shutdown()
{
	Logger::Warning("Engine shutting down...");

	Renderer::ShutDown();
	LevelManager::getInstance().ClearLevels();
	SDL_Quit();

	Logger::Display("Engine shut down");
}







