#pragma once
#include <algorithm>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string_view>
#include "GameObject.h"

class EntityManager
{
private:
	std::vector<GameObject*> entityGroup;

public:
	EntityManager();
	~EntityManager();

	void Init();
	void Start();
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw(float deltaTime);

	void AddEntity(GameObject* entity);
	void RemoveEntity(GameObject* entity);
	void ClearEntities();
	std::vector<GameObject*> getAllEntities() const;
};

