#pragma once
#include "Component.h"
#include "Aid/Transform.h"
#include <string>

class RE_API TextComponent : public Component
{
public:
	TextComponent();
	~TextComponent() = default;

	void SetText(std::string text, int x, int y, Vector2D scale);
	void SetText(std::string text);

	void Draw(float deltaTime) override;

protected:
	std::string m_Text;
	int m_X;
	int m_Y;
	Vector2D m_Scale;

};

