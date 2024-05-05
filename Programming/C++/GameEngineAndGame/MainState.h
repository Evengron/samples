#pragma once

#include "GameState.h"
#include "GameObjectManager.h"
#include "IRenderComponent.h"

class MainState : public GameState
{
public:
	MainState(GameStateManager* gameStateManager, Game* game);

	void init() override;
	void exit() override;

	void update(float deltaTime) override;
	void draw() override;

private:
	GameObjectManager m_gameObjectManager;

	std::vector<IRenderComponent::ptr> m_renderComponentsVec;
};
