#include "Level.h"
#include "ECS\GameObject.h"
#include "ECS\EntityManager.h"
#include "Aid\Logger.h"

Level::Level()
{
	m_entityManager = new EntityManager();
}

void Level::OpenLevel()
{
	//Create the entities [GameSide]
	//Speakers, Lights or Cameras can be created here for a better default level [EngineSide]
}

void Level::Init()
{
	m_entityManager->Init();
}

void Level::Start()
{
	m_entityManager->Start();
}

void Level::Update(float deltaTime)
{
	m_entityManager->Update(deltaTime);
}

void Level::LateUpdate(float deltaTime)
{
	m_entityManager->LateUpdate(deltaTime);
}

void Level::Draw(float deltatime)
{
	m_entityManager->Draw(deltatime);
}

void Level::Shutdown()
{
	//Called when engine is shutting down
	ClearGameObjects();
}

void Level::AddGameObject(GameObject* gameObject)
{
	m_entityManager->AddEntity(gameObject);
}

void Level::RemoveGameObject(GameObject* gameObject)
{
	m_entityManager->RemoveEntity(gameObject);
}

void Level::ClearGameObjects()
{
	//meant to be called in run time
	m_entityManager->ClearEntities();
}
