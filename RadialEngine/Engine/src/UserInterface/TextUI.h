#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Core/Core.h"
#include "Aid/Transform.h"
#include "ECS/ECS.h"

class RE_API TextUI {

public:
	void PrintSreen(std::string text, int x, int y, Vector2D scale, int spacing = 2000);
	class Font* GetFontHandle() const { return m_Font; }
	static TextUI* GetInstance()
	{
		static TextUI m_Instance;
		return &m_Instance;
	}
private:
	TextUI();
	class Font* m_Font;
	inline inline static TextUI* m_Instance = nullptr;
};
