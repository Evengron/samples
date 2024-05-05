#include "stdafx.h"

#include "GameObject.h"
#include "PlayerMoveComponent.h"
#include "InputManager.h"
#include "VectorAlgebra2D.h"

PlayerMoveComponent::PlayerMoveComponent(
	GameObject& game_object, const int player_index)
	: IComponent(game_object)
	, mPlayerIndex(player_index)
{
}

bool
PlayerMoveComponent::init()
{
	return true;
}

void
PlayerMoveComponent::update(const float delta_time)
{
	const auto speed = 1'000.0f; // pixels/second 
	const auto rotationSpeed = 100.0f;

	float rotation = 0.0f;
	if (InputManager::get_instance().isKeyDown("right", mPlayerIndex))
		rotation = rotationSpeed * delta_time;
	if (InputManager::get_instance().isKeyDown("left", mPlayerIndex))
		rotation = -1.f * rotationSpeed * delta_time;

	Vector2f translation{0.0f, -1.0f};
	if (InputManager::get_instance().isKeyDown("up", mPlayerIndex))
	{
		MathUtil::rotate(translation, m_gameObject.getRotation());
		m_gameObject.move(translation * speed * delta_time);
	}
	
	m_gameObject.rotate(rotation);
	
}
