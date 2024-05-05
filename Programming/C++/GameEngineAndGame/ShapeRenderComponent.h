#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "IRenderComponent.h"

class ShapeRenderComponent : public IRenderComponent
{
public:
	using ptr = std::shared_ptr<ShapeRenderComponent>;

	ShapeRenderComponent(GameObject &gameObject, 
						 RenderWindow &renderWindow,
						 std::shared_ptr<sf::Shape> shape);

	virtual ~ShapeRenderComponent() = default;
	ShapeRenderComponent(const ShapeRenderComponent& copy) = delete;
	ShapeRenderComponent& operator=(const ShapeRenderComponent& rhv) = delete;

	virtual bool init() override;
	virtual void update(float deltaTime) override {}
	virtual void draw() override;

	Shape& getShape() { return *m_shape;  }

private:

	// Shape must be a pointer and cannot be an instance like a sprite, because
	// Shape is an abstract class. Therefore, it cannot be instantiated (compiler error)
	std::shared_ptr<Shape> m_shape;
};