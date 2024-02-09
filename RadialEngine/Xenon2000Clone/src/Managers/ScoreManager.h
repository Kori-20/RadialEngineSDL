#pragma once


class ScoreManager
{
private:
	static inline ScoreManager* myScoreM = nullptr;

	class GameUi* gameUi;

	int score = 0;
	int highScore = 0;

public:
	static ScoreManager& GetInstance()
	{
		static ScoreManager myScoreM;
		return myScoreM;
	}

	~ScoreManager() = default;

	void SetGameUi(class GameUi* _gameUi) { gameUi = _gameUi; }
	void AddScore(int addedScore);
};

