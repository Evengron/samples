#include "stdafx.h"

#include "MenuState.h"

#include "Game.h"
#include "GameStateManager.h"

#include "InputManager.h"

using namespace std;

void
MenuState::init()
{
	if (m_isInit)
		return;

	if (!m_font.loadFromFile("../assets/arial.ttf"))
	{
		err() << "Could not load font\n";
		return;
	}
	m_text.setPosition(m_game->getWindow().getView().getCenter());
	m_text.setString("Press space to continue");
	m_text.setFillColor(Color::White);
	m_text.setFont(m_font);
	m_text.setOrigin(
		m_text.getLocalBounds().width * 0.5f,
		m_text.getLocalBounds().height * 0.5f);

	m_view = m_game->getWindow().getView();

	m_isInit = true;
}

void MenuState::update(float delta)
{
	m_game->getWindow().setView(m_view);

	if (InputManager::get_instance().isKeyPressed("Select"))
		mGameStateManager->setState("MainState");
}

void MenuState::draw()
{
	m_game->getWindow().draw(m_text);
}
