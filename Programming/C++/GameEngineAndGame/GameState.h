#pragma once

#include <memory>

class GameStateManager;
class Game;

class GameState
{
public:
	using ptr = std::shared_ptr<GameState>;

	GameState(GameStateManager* gameStateManager, Game* game)
		: mGameStateManager(gameStateManager)
		, m_game(game)
	{
	}

	virtual ~GameState() = default;

	/// called when game state is entered.
	virtual void init()
	{
	};

	/// called when game state is left.
	virtual void exit()
	{
	};

	virtual void update(float delta) = 0;
	virtual void draw() = 0;

protected:
	GameStateManager* mGameStateManager;
	Game* m_game;
};
