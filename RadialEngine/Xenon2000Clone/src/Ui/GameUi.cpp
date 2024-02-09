#include "GameUi.h"
#include <iomanip>

GameUi::GameUi()
{
	playerOneText = &AddComponent<TextComponent>();
	playerOneText->SetText("Player One", 5, 20, Vector2D(.5f, .5f));
	currentScore = &AddComponent<TextComponent>();
	currentScore->SetText("0000000000", 5, 50, Vector2D(.8f, .8f));

	highScoreText = &AddComponent<TextComponent>();
	highScoreText->SetText("High Score", 350, 20, Vector2D(.4f, .4f));
	highScoreValue = &AddComponent<TextComponent>();
	highScoreValue->SetText("0000000000", 350, 40, Vector2D(.4f, .4f));
}

GameUi::~GameUi()
{

}

void GameUi::UpdateScore(int newValue)
{
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(10) << newValue;
	std::string formattedScore = ss.str();

	currentScore->SetText(formattedScore);
	highScoreValue->SetText(formattedScore);// highscore not implemented, need a way to save highschore ignore for now
}

