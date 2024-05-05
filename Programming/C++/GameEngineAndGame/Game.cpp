#include "stdafx.h"

#include "Game.h"

#include "InputManager.h"
#include "MenuState.h"
#include "MainState.h"
#include "DebugDraw.h"

using namespace std;


void Game::run()
{
	if (!init())
		return;

	while (m_window.isOpen())
	{
		// process events in the input manager
		Event event{};
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				m_window.close();
			else
				m_inputManager->process(event);
		}

		update();
		draw();
	}

	shutdown();
}

bool Game::init()
{
	m_inputManager = &InputManager::get_instance();

	m_inputManager->bind("Exit", Keyboard::Escape);
	m_inputManager->bind("Select", Keyboard::Space);

	// May move to view later on
	m_inputManager->bind("up", Keyboard::Up, 0);
	m_inputManager->bind("left", Keyboard::Left, 0);
	m_inputManager->bind("down", Keyboard::Down, 0);
	m_inputManager->bind("right", Keyboard::Right, 0);

	m_inputManager->bind("up", Keyboard::W, 1);
	m_inputManager->bind("down", Keyboard::S, 1);
	m_inputManager->bind("left", Keyboard::A, 1);
	m_inputManager->bind("right", Keyboard::D, 1);


	m_inputManager->bind("debugdraw", Keyboard::F1, 0);

	m_debugDraw = &DebugDraw::get_instance();

	//
	m_gameStateManager.registerState("MenuState", make_shared<MenuState>(&m_gameStateManager, this));
	m_gameStateManager.registerState("MainState", make_shared<MainState>(&m_gameStateManager, this));

	//
	m_window.create(VideoMode(m_config.m_resolution.x, m_config.m_resolution.y),
		m_config.m_windowName);

	m_inputManager->setRenderWindow(&m_window);

	m_gameStateManager.setState("MenuState");

	return true;
}

void Game::update()
{
	// starts the clock
	static Clock clock;
	// restart takes time
	auto delta_time = clock.restart();
	const auto f_delta_time_seconds = delta_time.asSeconds();

	// must be first call
	m_inputManager->update();

	m_gameStateManager.update(f_delta_time_seconds);

	m_debugDraw->update(f_delta_time_seconds);
}

void Game::draw()
{
	m_window.clear();

	m_gameStateManager.draw();

	m_debugDraw->draw(m_window);

	m_window.display();
}

void Game::shutdown()
{
}
