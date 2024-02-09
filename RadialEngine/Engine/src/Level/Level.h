#pragma once
#include <vector>
#include "Aid/Logger.h"
#include "ECS/ECS.h"

class GameObject;

class RE_API Level
{
public:
	Level(); //Creates an EntityManager that will take care of all the game objects in the level
	~Level() = default;

	class EntityManager* GetEntityManager() const { return m_entityManager; }

	virtual void OpenLevel();//Holds the declaration of entitities game Side //Called by EngineCore loop 
	//Has to be called before Init so that the entities get added to the list 
	//before The Init()->EnityManager->Init() is called, so that the Entity Manager can initialize the entities

	void Init();// Call Entity Manager Init //Called by EngineCore loop
	void Start();// Call Entity Manager Start //Called by EngineCore loop
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw(float deltatime);

	void Shutdown();//Not called by engine flow

	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);
	void ClearGameObjects();

private:
	class EntityManager* m_entityManager = nullptr;//Defined in the constructor
	class GameManager* m_gameManager = nullptr;
	std::vector<GameObject*> m_gameObjects; //Holds all the game objects in the level
};

