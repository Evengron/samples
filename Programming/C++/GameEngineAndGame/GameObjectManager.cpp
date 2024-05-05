#include "stdafx.h"

#include "Debug.h"

#include "GameObjectManager.h"

void GameObjectManager::init()
{
}

void GameObjectManager::shutdown()
{
	m_gameObjects.clear();
}

void
GameObjectManager::addGameObject(const GameObject::ptr& gameObject)
{
	FF_ASSERT_MSG(m_gameObjects.find(gameObject->getId()) == m_gameObjects.end(),
		"Game object with this m_id already exists " + gameObject->getId());

	m_gameObjects[gameObject->getId()] = gameObject;
}

GameObject::ptr GameObjectManager::getGameObject(const std::string& id) const
{
	const auto it = m_gameObjects.find(id);
	if (it == m_gameObjects.end())
	{
		FF_ERROR_MSG("Could not find gameobject with m_id " + id);
		return nullptr;
	}
	return it->second;
}
