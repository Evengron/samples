#include "stdafx.h"

#include "GameObject.h"

void
GameObject::addComponent(const IComponent::ptr& component)
{
	m_componentList.push_back(component);
}

void GameObject::update(const float deltaTime)
{
	for (const auto& comp : m_componentList)
		comp->update(deltaTime);
}

bool GameObject::init()
{
	for (const auto& comp : m_componentList)
	{
		if (!comp->init())
		{
			err() << "Could not initialize component of object " << m_id << std::endl;
			return false;
		}
	}
	return true;
}
