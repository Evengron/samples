#include "stdafx.h"
#include "DebugDraw.h"
#include "VectorAlgebra2D.h"
#include "InputManager.h"


DebugDraw::DebugDraw() :
	m_enabled(true)
{
	if (!m_font.loadFromFile("../assets/consolab.ttf"))
	{
		err() << "Could not load font\n";
	}
};

void DebugDraw::drawLine(const Vector2f& p1, const Vector2f& p2, const Color& color, const float thickness)
{
	if (!m_enabled)
	{
		return;
	}

	auto dir = p2 - p1;
	const auto length = MathUtil::length(dir);

	if (length >= 1.0f)
	{
		dir = (dir / length) * thickness * 0.5f;
		const Vector2f right(dir.y, -dir.x);

		std::shared_ptr<ConvexShape> shape(new ConvexShape());
		shape->setPointCount(4);
		shape->setPoint(0, p1 - right);
		shape->setPoint(1, p1 + right);
		shape->setPoint(2, p2 + right);
		shape->setPoint(3, p2 - right);
		shape->setFillColor(color);

		m_shapes.push_back(shape);
	}
}

void DebugDraw::drawArrow(const Vector2f& origin, const Vector2f& direction, const Color& color, const float thickness)
{
	if (!m_enabled)
	{
		return;
	}

	const auto length = MathUtil::length(direction);

	if (length >= 1.0f)
	{
		const auto unit_direction = direction / length;
		const Vector2f right(unit_direction.y, -unit_direction.x);

		const auto head_size = 5.0f;
		const auto head = length > (head_size * 2) ? length - head_size : length * 0.5f;

		const auto p1 = origin;
		const auto p2 = origin + unit_direction * head;
		const auto p3 = origin + direction;

		std::shared_ptr<ConvexShape> shape(new ConvexShape());
		shape->setPointCount(4);

		shape->setPoint(0, p1 - right * thickness * 0.5f);
		shape->setPoint(1, p1 + right * thickness * 0.5f);
		shape->setPoint(2, p2 + right * thickness * 0.5f);
		shape->setPoint(3, p2 - right * thickness * 0.5f);
		shape->setFillColor(color);

		m_shapes.push_back(shape);

		std::shared_ptr<ConvexShape> head_shape(new ConvexShape());
		head_shape->setPointCount(3);

		head_shape->setPoint(0, p2 - right * head_size);
		head_shape->setPoint(1, p2 + right * head_size);
		head_shape->setPoint(2, p3);
		head_shape->setFillColor(color);

		m_shapes.push_back(head_shape);
	}
}

void DebugDraw::drawCircle(const Vector2f& center, const float radius, const Color& outline_color, const Color& fill_color)
{
	if (!m_enabled)
	{
		return;
	}

	std::shared_ptr<CircleShape> shape(new CircleShape(radius));
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(outline_color);
	shape->setFillColor(fill_color);
	shape->setPosition(center);
	shape->setOrigin(Vector2f(radius, radius));

	m_shapes.push_back(shape);
}

void DebugDraw::drawRectangle(const Vector2f& position, const Vector2f& size, const Color& outline_color,
	const Color& fill_color)
{
	if (!m_enabled)
	{
		return;
	}

	std::shared_ptr<RectangleShape> shape(new RectangleShape(size));
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(outline_color);
	shape->setFillColor(fill_color);
	shape->setPosition(position);
	shape->setOrigin(size * 0.5f);

	m_shapes.push_back(shape);
}

void DebugDraw::drawText(const std::string& str, const Vector2f& center, const Color& color)
{
	std::shared_ptr<Text> text(new Text());
	text->setPosition(center);
	text->setString(str);
	text->setFillColor(color);
	text->setFont(m_font);
	text->setCharacterSize(14);
	const auto bounds = text->getLocalBounds();
	text->setOrigin(
		bounds.width * 0.5f,
		bounds.height * 0.5f + bounds.top);

	m_shapes.push_back(text);
}

void DebugDraw::update(float delta_time)
{
	if (InputManager::get_instance().isKeyReleased("debugdraw"))
	{
		setEnabled(!isEnabled());
	}
}

void DebugDraw::draw(RenderWindow& render_window)
{
	if (m_enabled)
	{
		for (const auto& shape : m_shapes)
		{
			render_window.draw(*shape);
		}
	}

	m_shapes.clear();
}
