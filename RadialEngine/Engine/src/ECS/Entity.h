#pragma once
#include <memory>
#include <vector>
#include "Component.h"
#include "ECS.h"
#include "Aid\Transform.h"

class Entity
{
	//friends
	friend class EntityManager;
	friend class GameObject;

public:
	Entity() = default;
	virtual ~Entity() = default;

	template<typename T, typename... TArgs>
	constexpr inline T& AddComponent(TArgs&&... args)//adds a component to the entity
	{
		T* comp(new T(std::forward<TArgs>(args)...));//creates a new component

		std::shared_ptr<Component> uptr{ comp };//creates a shared pointer to the component
		compGroup.emplace_back(std::move(uptr));//adds the component to the components vector
		m_compArray[GetComponentTypeID<T>()] = comp;//adds the component to the component array
		m_compBitset[GetComponentTypeID<T>()] = true;//sets the component bitset to true
		comp->SetOwner(this);//sets the component owner to this entity

		return *comp;
	}

	template<typename T>
	constexpr inline T& GetComponent() const//gets a component from the entity
	{
		auto ptr(m_compArray.at(GetComponentTypeID<T>()));
		return *static_cast<T*>(ptr);
	}

	template<typename T>
	inline bool HasComponent() const //checks if the entity has a component
	{
		return m_compBitset[GetComponentTypeID<T>()];
	}

	virtual void Init()
	{
		for (const auto& comp : compGroup)
		{
			comp->Init();
		}
	}

	virtual void Start()
	{
		for (const auto& comp : compGroup)
		{
			comp->Start();
		}
	}

	virtual inline void Draw(float deltaTime)
	{
		for (const auto& comp : compGroup)
		{
			comp->Draw(deltaTime);
		}
	}

	virtual inline void Update(float deltaTime)
	{
		for (const auto& comp : compGroup)
		{
			comp->Update(deltaTime);
		}
	}

	inline bool IsActive() const
	{
		return m_active;
	}

	inline void Destroy()
	{
		m_active = false;
	}


	inline void SetLayer(int newLayer) //Layer only has purpose for rendering order
	{
		layer = newLayer;
	}

	inline int GetLayer() const
	{
		return layer;
	}

private:
	Vector2D objPosition;
	bool m_active = true;
	ComponentArray m_compArray{};
	ComponentBitset m_compBitset;

	int layer = 1;//layer 999 is to be used excusively by Ui  

	std::vector<std::shared_ptr<Component>> compGroup;

};

