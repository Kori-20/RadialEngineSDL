#pragma once
#include "Aid/MathTools.h"
#include "Aid/Transform.h"
#include <vector>
#include "ECS/Entity.h"

enum Tag
{
	Player,
	Ally,
	Enemy,
	Projectile,
	EnemyProjectile,
	Obstacle,
	Pickup,
	Manager,
};

class RE_API GameObject : public Entity
{
public:
	enum Space { LOCAL = 0, WORLD = 1 };

	GameObject();
	GameObject(Vector2D pos);
	GameObject(float x, float y);

	~GameObject();

	virtual void Init() override;
	virtual void Start() override;
	//Aditional
	virtual void Update(float deltaTime) override;
	virtual void Draw(float deltaTime) override;

	//Collision game side fucntions
	virtual void OnCollisionStart(GameObject* other){};
	virtual void OnCollisionEnd(GameObject* other){};
	virtual void OnOverlapBegin(GameObject* other){};
	virtual void OnOverlapEnd(GameObject* other){};
	//Player can use them to execute code on specific moments 

	void SetID(int id) { ID = id; }
	int GetID() { return ID; }

private:
	float rotation;
	float scale = 1; //1 by default

	bool isActive = true;//true by default
	GameObject* parent = nullptr;//null by default

	std::vector<Tag> objectTags; // Vector to hold object tags

	int ID = 0;

	void ObjectSetup();

protected:
	Transform* transform;

public:

	//Setters
	virtual void SetParent(GameObject* parent);
	virtual void SetRotation(float rot);
	virtual void SetActive(bool active);
	virtual void SetScale(float scale);
	//Tagging
	virtual void AddTag(Tag tag);
	virtual void RemoveTag(Tag tag);//Has very unique use cases, but can be useful
	virtual bool HasTag(Tag tag);//checks if object has a tag
	//Getters
	GameObject* GetParent();
	Vector2D GetPosition(Space space = WORLD);
	Transform* GetTransform() { return transform; }
	float GetRotation(Space space = WORLD);

	bool IsActive();
};

