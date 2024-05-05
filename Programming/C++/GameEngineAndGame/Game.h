#pragma once

#include <string>

#include "GameStateManager.h"

class InputManager;
class DebugDraw;

class Game
{
public:
	struct Config
	{
		Vector2i m_resolution{ 800, 600 };
		std::string m_windowName = "FinalFrontier";
	};

	Config &getConfig() { return m_config; }
	RenderWindow &getWindow() { return m_window; }

	void run();

private:

	bool init();
	void update();
	void draw();
	static void shutdown();

	Config m_config;

	RenderWindow m_window;
	GameStateManager m_gameStateManager;

	InputManager* m_inputManager = nullptr;
	DebugDraw* m_debugDraw = nullptr;
};
