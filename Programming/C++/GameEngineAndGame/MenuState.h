#pragma once

#include "GameState.h"

#include <SFML/Graphics/Text.hpp>

class MenuState : public GameState
{
public:
	using GameState::GameState;

	void init() override;

	void update(float delta) override;
	void draw() override;

private:
	// should be gameobject too
	Text m_text;
	Font m_font;
	View m_view;

	bool m_isInit = false;
};
