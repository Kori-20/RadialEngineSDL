#include "TextUI.h"
#include "Font.h"

void TextUI::PrintSreen(std::string text, int x, int y, Vector2D scale, int spacing)
{
	m_Font->RenderText(text, x, y, Vector2D(scale.x/100, scale.y/100), spacing);
}

TextUI::TextUI()
{
	m_Font = new Font();
}
