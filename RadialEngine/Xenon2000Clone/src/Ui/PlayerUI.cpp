#include "PlayerUI.h"

PlayerUI::PlayerUI()
{
	transform->SetPosition(10, 590);

	HpBar = &AddComponent<SpriteComponent>("Assets/PNG/Healthbar.png",.62,.10,.5);
	HpBar->numberOfCollums = 1;
	HpBar->numberOfRows = 1;
	HpBar->isAnimated = false;

	HpBarBorder = &AddComponent<SpriteComponent>("Assets/PNG/healthbarback.png",.62,.10,.5);
	HpBarBorder->numberOfCollums = 1;
	HpBarBorder->numberOfRows = 1;
	HpBarBorder->isAnimated = false;

	SetLayer(990);
}

PlayerUI::~PlayerUI()
{

}

void PlayerUI::UpdateUiValues(TextComponent uiElement, std::string newValue)
{

}
