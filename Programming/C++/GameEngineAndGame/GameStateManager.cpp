#include "stdafx.h"

#include "GameStateManager.h"
#include <utility>
#include "GameState.h"
#include "Debug.h"

void GameStateManager::registerState(const std::string& name, GameState::ptr state)
{
	states[name] = std::move(state);
}

void GameStateManager::setState(const std::string& stateName)
{
	GameState* state = findState(stateName);
	FF_ASSERT_MSG(state != nullptr, "State could not be found");

	m_futureState = state;
}

void GameStateManager::changeState(GameState* state)
{
	if (state != m_currentState)
	{
		if (m_currentState != nullptr)
			m_currentState->exit();

		m_currentState = state;

		if (m_currentState != nullptr)
			m_currentState->init();
	}
}

void GameStateManager::update(float delta)
{
	if (m_futureState != nullptr)
	{
		changeState(m_futureState);
		m_futureState = nullptr;
	}

	if (m_currentState != nullptr)
		m_currentState->update(delta);
}

void GameStateManager::draw() const
{
	if (m_currentState != nullptr)
		m_currentState->draw();
}

GameState* GameStateManager::findState(const std::string& stateName)
{
	const auto state = states.find(stateName);
	if (state != states.end())
		return state->second.get();
	return nullptr;
}
