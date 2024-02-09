#include "GameObject.h"
#include "Aid\Logger.h"
#include "Level/LevelManager.h"

GameObject::GameObject()
{
	ObjectSetup();
	transform->SetPosition(0, 0);
}

GameObject::GameObject(Vector2D pos)
{
	ObjectSetup();
	transform->SetPosition(pos.x, pos.y);
}

GameObject::GameObject(float x, float y)
{
	ObjectSetup();
	transform->SetPosition(x, y);
}

void GameObject::ObjectSetup()
{
	transform = &AddComponent<Transform>();
	LevelManager::getInstance().GetCurrentLevel()->AddGameObject(this);
}

GameObject::~GameObject()
{
	for (auto element : compGroup)
	{
		element.reset();
	}

	compGroup.clear();
}

void GameObject::Init()
{
	Entity::Init();
}

void GameObject::Start()
{
	Entity::Start();
}

void GameObject::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void GameObject::Draw(float deltaTime)
{
	Entity::Draw(deltaTime);
}

void GameObject::SetParent(GameObject* new_parent)
{
	//subtract the parent's position from the child's position to get the local position relative to the parent
	transform->SetPosition(GetPosition(WORLD) - parent->GetPosition(WORLD));
	GameObject* parent = new_parent;
}

void GameObject::SetActive(bool active)
{
	isActive = active;
}

void GameObject::SetScale(float scale)
{
	scale = scale;
}

GameObject* GameObject::GetParent()
{
	if (parent == nullptr) 
	{
		Logger::Warning("Parent is null");
	}
	return parent;
}

Vector2D GameObject::GetPosition(Space space)
{
	Vector2D objPos = transform->GetPosition();

	if (space == LOCAL || parent == nullptr){
		return objPos;
	}
	else{
		return parent->GetPosition(WORLD) + objPos.RotateVector(objPos, parent->GetRotation(LOCAL));
	}
}

float GameObject::GetRotation(Space space)
{
	if (space == LOCAL || parent == nullptr) {
		return rotation;
	}
	else {
		return parent->GetRotation(WORLD) + rotation;
	}
}

void GameObject::SetRotation(float rot)
{
	rotation = rot;
	if (rotation > 360){
		rotation -= 360;
	}

	else if (rotation < 0){
		rotation += 360;
	}
}

bool GameObject::IsActive()
{
	return isActive;
}

void GameObject::AddTag(Tag tag)
{
	if (HasTag(tag)) {
		Logger::Warning("Tag already exists");
	}

	//Logger::Info("Tag has been added");
	objectTags.push_back(tag);
}

void GameObject::RemoveTag(Tag tag)
{
	objectTags.erase(std::remove(objectTags.begin(), objectTags.end(), tag), objectTags.end());//remove the tag from the vector
	Logger::Info("Tag was sucessfuly removed");
}

bool GameObject::HasTag(Tag tag)
{
	auto tagSearch = std::find(objectTags.begin(), objectTags.end(), tag);
	if (tagSearch != objectTags.end()) //if the tag is found
	{
		return true;
	}
	return false;
}