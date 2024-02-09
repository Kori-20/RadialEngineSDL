#include "TextComponent.h"
#include "UserInterface/TextUI.h"
#include "ECS/Entity.h"

TextComponent::TextComponent()
{

}

void TextComponent::SetText(std::string text, int x, int y, Vector2D scale)
{
	m_Text = text;
	m_X = x;
	m_Y = y;
	m_Scale = scale;
	GetOwner()->SetLayer(999);//Set the layer to 999 so the text is always on top
}

void TextComponent::SetText(std::string text)
{
	m_Text = text;
}

void TextComponent::Draw(float deltaTime)
{
	TextUI::GetInstance()->PrintSreen(m_Text, m_X, m_Y, m_Scale);
}
