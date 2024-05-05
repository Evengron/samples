#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "IComponent.h"

class IRenderComponent : public IComponent
{
public:
	using ptr = std::shared_ptr<IRenderComponent>;
	using weak_ptr = std::weak_ptr<IRenderComponent>;

	IRenderComponent(GameObject& gameObject, RenderWindow& renderWindow)
		: IComponent(gameObject)
		, m_renderWindow(renderWindow)
	{
	}

	virtual void draw() = 0;

protected:
	RenderWindow& m_renderWindow;
};
