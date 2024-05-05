#include "stdafx.h"

#include "GameObject.h"
#include "TransformCopyComponent.h"

TransformCopyComponent::TransformCopyComponent(
	GameObject& gameObject, 
	GameObject& srcGameObject)
: IComponent(gameObject)
, m_srcGameObject(srcGameObject)
{
}

bool 
TransformCopyComponent::init()
{
	return true;
}

void TransformCopyComponent::update(const float fDeltaTime) 
{
	m_gameObject.setPosition(m_srcGameObject.getPosition());
	m_gameObject.move(m_offset);
}

