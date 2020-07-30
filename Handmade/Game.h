#ifndef GAME_H
#define GAME_H

#include <deque>
#include <string>
#include "GameState.h"

class Game
{

public:

	Game(GameState* initialGameState);

public:

	bool Initialize(const std::string& name, int screenWidth,
		            int screenHeight, bool fullscreen = false);
	bool Run();
	void ShutDown();

private:

	int m_deltaTime;
	GameState* m_gameState;

};

#endif