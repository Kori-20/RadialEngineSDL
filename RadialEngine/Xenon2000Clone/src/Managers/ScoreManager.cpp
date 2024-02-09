#include "ScoreManager.h"
#include "../Ui/GameUi.h"
#include <string>

void ScoreManager::AddScore(int addedScore)
{
	score += addedScore;
	gameUi->UpdateScore(score);
}
