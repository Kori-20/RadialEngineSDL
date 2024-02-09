#include "App.h"
#include "EngineCore.h"
#include <iostream>

App::App()
{
	m_EngineCore = EngineCore ::GetInstance();
}

void App::Run() // Main loop	
{
	m_EngineCore->Initialize();
	m_EngineCore->Start();

	while (m_EngineCore->GetIsRunning())
	{
		m_EngineCore->EventHandler();
		m_EngineCore->Update();
		m_EngineCore->Draw();
	}

	m_EngineCore->Shutdown();
}

