#include "stdafx.h"

#include "GameObject.h"
#include "ShapeRenderComponent.h"
#include <utility>

#include "Debug.h"

ShapeRenderComponent::ShapeRenderComponent(
	GameObject &gameObject, 
	RenderWindow &renderWindow,
	std::shared_ptr<sf::Shape> shape)
: IRenderComponent(gameObject, renderWindow)
, m_shape(std::move(shape))
{
}

bool
ShapeRenderComponent::init()
{
	if (!m_shape)
	{
		FF_ERROR_MSG("No renderable shape provided.");
		return false;
	}
	return true;
}

void
ShapeRenderComponent::draw()
{
	m_renderWindow.draw(*m_shape, m_gameObject.getTransform());
}
