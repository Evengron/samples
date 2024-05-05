#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "IRenderComponent.h"

class SpriteRenderComponent : public IRenderComponent
{
public:
	using Ptr = std::shared_ptr<SpriteRenderComponent>;

	SpriteRenderComponent(GameObject& gameObject,
		RenderWindow& renderWindow,
		std::string textureFile,
		const Color& maskColor = Color::Black);

	bool init() override;

	void update(float deltaTime) override
	{
	}

	void draw() override;

	Sprite& getSprite() { return m_sprite; }

	/// Move window over sprite texture
	//void setTextureRect(const IntRect &intRect);

private:
	std::string m_textureFile;
	Texture m_texture;
	Sprite m_sprite;
	Color m_maskColor;
};
