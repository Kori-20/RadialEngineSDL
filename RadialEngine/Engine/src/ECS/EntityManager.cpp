#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

void EntityManager::Init()
{
	for (auto& rE : entityGroup)
	{
		rE->Init();
	}
}

void EntityManager::Start()
{
	for (auto& rE : entityGroup)
	{
		rE->Start();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (int i = 0; i < entityGroup.size(); i++)
	{
		if (entityGroup[i]->m_active == false)
		{
			RemoveEntity(entityGroup[i]);
			continue;
		}
		entityGroup[i]->Update(deltaTime);
	}
}

void EntityManager::LateUpdate(float deltaTime)
{
	for (int i = 0; i < entityGroup.size(); i++)
	{
		
	}
}

void EntityManager::Draw(float deltaTime)
{

	// Sort the entities by layer before drawing
	std::stable_sort(entityGroup.begin(), entityGroup.end(), [](const GameObject* a, const GameObject* b)
	{
		return a->GetLayer() < b->GetLayer();
	});

	for (auto& rE : entityGroup)
	{
		rE->Draw(deltaTime);
	}
}

void EntityManager::AddEntity(GameObject* entity)
{
	entityGroup.push_back(entity);

	//Temporary ID System
	int newID = (entityGroup.size() - 1);
	entity->SetID(newID);
	Logger::Note("Obj created: " + std::to_string(newID));
}

void EntityManager::RemoveEntity(GameObject* entity)
{
	auto it = std::find(entityGroup.begin(), entityGroup.end(), entity);//find the entity
	if (it != entityGroup.end()) //if the entity is found
	{
		entityGroup.erase(it);//erase the entity

		//Temporary ID System
		int vacantID = entity->GetID();
		Logger::Warning("Obj removed: " + std::to_string(vacantID));
	}
	delete entity;//delete the entity 
}

void EntityManager::ClearEntities()
{
	entityGroup.clear();
}

std::vector<GameObject*> EntityManager::getAllEntities() const
{
	return entityGroup;
}
