#pragma once

#include <string>
#include <unordered_map>

#include "GameObject.h"

class GameObjectManager
{
public:
	using GameObjectMap = std::unordered_map<std::string, GameObject::ptr>;

	void init();
	void shutdown();

	void addGameObject(const GameObject::ptr& game_object);
	GameObject::ptr getGameObject(const std::string& id) const;

	GameObjectMap& getGameObjects() { return m_gameObjects; }

private:

	GameObjectMap m_gameObjects;
};
