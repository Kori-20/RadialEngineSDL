#include "LevelManager.h"
#include "Level.h"
#include "Aid\Logger.h"


LevelManager::LevelManager()
{
	currentLevelIndex = 0;
}

Level* LevelManager::GetCurrentLevel()
{
	m_currentlevel = levelsList.at(currentLevelIndex);
	return m_currentlevel;
}

void LevelManager::GoToLevel(int levelIndex)
{
	if (levelIndex == -1) {
		m_currentlevel = levelsList.at(currentLevelIndex);
		m_currentlevel->Init(); //cuz increment starts at 0
		currentLevelIndex++;
		if (currentLevelIndex <= levelsList.size()) {
			m_currentlevel = levelsList.at(currentLevelIndex);
		}
	}
	else {
		if (levelIndex <= levelsList.size()) {
			m_currentlevel = levelsList.at(levelIndex);
			m_currentlevel->Init();
			m_currentlevel->Start();
		}
		else 
		{
			Logger::Info("Level: " + std::to_string(levelIndex) + " does note exist");
		}
	}
}

void LevelManager::AddLevel(Level* level)
{
	if (levelsList.empty()) {
		levelsList.push_back(level);
		return;
	}

	for (const auto level : levelsList) {
		if (level != level) {
			levelsList.push_back(level);
		}
	}
}

void LevelManager::RemoveLevel(Level* level)
{
	auto it = std::find(levelsList.begin(), levelsList.end(), level);
	if (it != levelsList.end()) 
	{
		level->Shutdown();
		levelsList.erase(it);
	}
	
}

void LevelManager::ClearLevels()
{
	for (auto& level : levelsList)
	{
		level->Shutdown(); // Assuming Shutdown is a method that cleans up resources
		delete level; // Deleting the Level object
	}

	levelsList.clear(); // Clearing the list itself
	Logger::Issue("All levels were shutdown");
}

void LevelManager::NextLevel()
{
	currentLevelIndex++;
}
