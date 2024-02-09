#pragma once
#include "App.h"
#include "..\Aid\Logger.h"
#include "..\Level\LevelManager.h"

#ifdef RE_PLATFORM_WINDOWS

//TODO:: Find a way to have the entry point be unchangable by the user 

extern App* CreateApplication();

int main(int argc, char** argv)//Acess point used from game side to start the engine
{
	Logger::Note("Engine Entry Point...");
	App* newApp = CreateApplication();
	newApp->Run();
	delete newApp;
}
#endif
