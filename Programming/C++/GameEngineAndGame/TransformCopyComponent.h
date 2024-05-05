#pragma once

#include "IComponent.h"

class TransformCopyComponent : public IComponent
{
public:
	using ptr = std::shared_ptr<TransformCopyComponent>;

	TransformCopyComponent(GameObject& gameObject,
						   GameObject& srcGameObject);

	virtual bool init() override;
	virtual void update(float fDeltaTime) override;

	void setOffset(const sf::Vector2f& offset) 
	{
		m_offset = offset;	
	}
	sf::Vector2f get_offset() const 
	{ 
		return m_offset; 
	}

private:

	GameObject& m_srcGameObject;
	Vector2f m_offset{};
};