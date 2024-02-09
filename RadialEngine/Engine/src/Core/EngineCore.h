#pragma once
#include <vector>
#include <memory>
#include "Aid\Logger.h"
#include "Window.h"
#include "Input/Controller.h"
#include "Input\InputHandler.h"
#include "UserInterface\TextUI.h"

#ifndef GAME_ENGINE_CORE_H
#define GAME_ENGINE_CORE_H

class EngineCore {
public:
	EngineCore();
	~EngineCore() = default;

	//Engine flux is defined by App.cpp
	void Initialize();
	void Start();
	void Update();
	void EventHandler();
	void Draw();
	void Shutdown();

	//Temporary Input Implementation 
	bool isSpaceKeyDown = false;
	bool isLeftKeyDown = false;
	bool isRightKeyDown = false;
	bool isUpKeyDown = false;
	bool isDownKeyDown = false;

private:

	bool isRunning = true;
	Window* gameWindow;
	static EngineCore* m_engine;

	class InputHandler* input_handle;
	static SDL_Event _sdlEvent;
	class SDLWrapper* sdlWrap;
	class FontLoader* fontLoader;

	//Frame rate related
	const int maxFPS = 144;//60 120 144
	double lastFrameTime;
	Uint64 m_TicksCount;
	Uint32 fpsTimerStart;
	Uint32 frameCount;
	Uint32 frameDelay;
	int lockFPS;
	// Timing related
	static float m_deltaTime;
	float targetDeltaTime;

public:
	const Uint8* keyState;
	InputHandler* GetInputHandler() const { { return InputHandler::GetInstance(); } }
	static EngineCore* GetInstance() { return  m_engine = (m_engine != nullptr) ? m_engine : new EngineCore(); }

	float GetDeltaTime() const { return m_deltaTime; }
	bool GetIsRunning() { return isRunning; }
	void SetIsRunning(bool isRunning) { this->isRunning = isRunning; }
	void GetWindow() { gameWindow->GetWindow(); }
	FontLoader* GetFontLoader() { return fontLoader; }

private:
	
	int roundedFPS = maxFPS;

	void DisplayFPS()//In header file to allow for a cleaner cpp file
	{
		Uint64 currentTicks = SDL_GetTicks();//GetTicks() returns the number of milliseconds since the SDL library initialization.
		frameCount++;

		if (currentTicks - fpsTimerStart >= 1000) //If one second has passed
		{
			float elapsedSeconds = static_cast<float>(currentTicks - fpsTimerStart) / 1000.0f; //Convert milliseconds to seconds
			float actualFPS = frameCount / elapsedSeconds;//Calculate the FPS
			roundedFPS = static_cast<int>(actualFPS);
			//Logger::Display("FPS: " + std::to_string(roundedFPS));

			fpsTimerStart = currentTicks; //Reset the FPS timer
			frameCount = 0;//Reset the FPS counter
		}
	}
	///Logger::Issue("m_dt " + std::to_string(m_deltaTime));
	///Logger::Warning("tdt " + std::to_string(targetDeltaTime));
	/// m_deltaTime is the time it took to complete the frame ->ex.: 0.0166666666666667 or 0.0333333333333333 or 0.0666666666666667
	/// targetDeltaTime is the time we want to complete the frame -> 1/60 = 0.0166666666666667
};

#endif GAME_ENGINE_CORE_H
