#pragma once

#pragma once

#include <list>
#include <string>

#include <SFML/Graphics/Transform.hpp>
#include <utility>

#include "IComponent.h"

class GameObject:public Transformable
{
public:
	using ptr = std::shared_ptr<GameObject>;

	GameObject(std::string id)
		: m_id(std::move(id))
	{
	}

	/// Add a component to the game object. Internally the game object
	/// identifies if it's a drawable component to call it's draw
	/// function or a general update component to call it's update
	/// function.
	/// \param component the component
	void addComponent(const IComponent::ptr& component);

	/// Returns the component of the given type
	template <typename TComponent>
	std::shared_ptr<TComponent> getComponent()
	{
		for (auto component : m_componentList)
		{
			if (std::shared_ptr<TComponent> cmp = std::dynamic_pointer_cast<TComponent>(component))
			{
				return cmp;
			}
		}
		return nullptr;
	}

	/// Initialize all added components
	bool init();

	/// Could also be moved out of game object in the long run.
	void update(float deltaTime);

	//// TODO: implement deletion mechanism
	bool isMarkedForDelete() const { return m_WantToDie; }
	void markForDelete() { m_WantToDie = true; }

	std::string getId() const { return m_id; }
	void setId(const std::string& id) { m_id = id; }

protected:
	std::string m_id = "unnamed"; //< unique name of object, e.g., player
	bool m_WantToDie = false;

	std::list<IComponent::ptr> m_componentList;
};
