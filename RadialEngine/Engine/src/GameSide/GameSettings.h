#pragma once
#include <string>

//TODO:: Implement this class, allow player to set window size, title, brightness, etc... Game side
class GameSettings
{
private:
	int gs_windowWidth;
	int gs_windowHeight;
	std::string gs_windowTitle;
	const int gs_maxFPS;

	int gs_brightness;

};

