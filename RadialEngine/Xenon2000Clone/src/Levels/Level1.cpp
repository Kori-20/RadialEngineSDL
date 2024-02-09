#include "Level1.h"
#include "Aid/Logger.h"
#include "../GameObjects/Scenery/BackgroundSprite.h"
#include "../GameObjects/PlayerRelated/PlayerShip.h"
#include "../GameObjects/Rock1.h"
#include "../GameObjects/Scenery/ParalaxBackground.h"
#include "../GameObjects/Bullet.h"
#include "../GameObjects/Enemies/TestEnemy.h"
#include "../Ui/GameUi.h"
#include "../Managers/ScoreManager.h"
#include "../Ui/PlayerUI.h"

void Level1::OpenLevel()
{
	GameUi* gameUi = new GameUi();
	PlayerUI* playerUi = new PlayerUI();
	ScoreManager::GetInstance().SetGameUi(gameUi);

	BackgroundSprite* bckg = new BackgroundSprite();
	ParalaxBackground* paraLayer = new ParalaxBackground();

	PlayerShip* player = new PlayerShip();

	TestEnemy* enemy1 = new TestEnemy(100, 200);
	TestEnemy* enemy2 = new TestEnemy(200, 200);

	TestEnemy* enemy3 = new TestEnemy(300, 400);
	enemy3->move = false;
	TestEnemy* enemy4 = new TestEnemy(400, 400);
	enemy4->move = false;

	TestEnemy* enemy5 = new TestEnemy(500, 200);
	TestEnemy* enemy6 = new TestEnemy(600, 200);

	Rock1* rock1 = new Rock1();
}
