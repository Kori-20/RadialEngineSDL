#pragma once
#include "Core.h"

class RE_API App
{
public:
	App();
	~App() = default; //C++ 20 Dosn't need virtual destructor

	void Run();

private:

	class EngineCore* m_EngineCore;

};

//To be defined in CLIENT
App* CreateApplication();