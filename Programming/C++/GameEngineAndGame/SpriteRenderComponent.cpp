#include "stdafx.h"

#include "GameObject.h"
#include "SpriteRenderComponent.h"
#include <utility>

SpriteRenderComponent::SpriteRenderComponent(
	GameObject& gameObject,
	RenderWindow& renderWindow,
	std::string textureFile,
	const Color& maskColor)
	: IRenderComponent(gameObject, renderWindow)
	, m_textureFile(std::move(textureFile))
    , m_maskColor(maskColor)
{
}

bool SpriteRenderComponent::init()
{
	Image image;
	if (!image.loadFromFile(m_textureFile))
	{
		err() << "Could not load texture from " << m_textureFile << std::endl;
		return false;
	}
	image.createMaskFromColor(m_maskColor);
	m_texture.loadFromImage(image);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x*0.5f, m_texture.getSize().y * 0.5f);

	return true;
}

void SpriteRenderComponent::draw()
{
	// TODO: adapt transform to have pixel precise movement
	m_renderWindow.draw(m_sprite, m_gameObject.getTransform());
}
