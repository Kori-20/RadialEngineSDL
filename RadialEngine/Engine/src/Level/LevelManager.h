#pragma once
#include <vector>
#include "Level.h"
#include "Aid/Transform.h"
#include <cassert>

class RE_API LevelManager
{
private:
	//Singleton pattern
	static inline  LevelManager* instance = nullptr;

	~LevelManager() = default;

public:
	//Singleton pattern
	static LevelManager& getInstance()
	{
		static LevelManager instance;  
		return instance;
	}

	static class Level* GetCurrentLevel();
	static void GoToLevel(int levelIndex = -1);
	static void AddLevel(Level* level);
	static void RemoveLevel(Level* level);
	static void ClearLevels();
	static void NextLevel();

	template <typename T, typename... TArgs>
	static T& InstantiateObject(Vector2D _position, GameObject& owner)
	{
		T* createdObj = new T();
		assert(static_cast<GameObject*>(createdObj));
		createdObj->GetTransform()->SetPosition(Vector2D(_position.x, _position.y));
		//createdObj->SetOwner(owner);
		createdObj->Init();
		return *createdObj;
	}

private:
	LevelManager();
	static inline Level* m_currentlevel{};
	static inline std::vector<Level*> levelsList;
	static inline int currentLevelIndex = 0;
};

