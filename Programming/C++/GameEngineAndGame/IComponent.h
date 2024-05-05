#pragma once

#include <memory>

class GameObject;

class IComponent
{
public:
	using ptr = std::shared_ptr<IComponent>;

	IComponent(GameObject& game_object)
		: m_gameObject(game_object)
	{
	}

	virtual ~IComponent() = default;

	virtual bool init() = 0;
	virtual void update(float delta_time) = 0;

protected:

	GameObject& m_gameObject;
};
