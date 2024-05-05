#include "stdafx.h"

#include "GameObject.h"
#include "CameraRenderComponent.h"

CameraRenderComponent::CameraRenderComponent(
	GameObject& gameObject,
	RenderWindow& renderWindow,
	View view)
	: IRenderComponent(gameObject, renderWindow)
	, m_view(view)
	, m_initialCenter(view.getCenter())
{
}

bool CameraRenderComponent::init()
{
	return true;
}

void CameraRenderComponent::draw()
{
}

void CameraRenderComponent::update(float deltaTime)
{
	const auto newCenter = m_gameObject.getTransform().transformPoint(m_initialCenter);
	m_view.setCenter(newCenter);

	auto view = m_view;
	view.setCenter(floor(view.getCenter().x), floor(view.getCenter().y));
	m_renderWindow.setView(view);
}
