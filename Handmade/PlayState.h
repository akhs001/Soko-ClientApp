#ifndef PLAY_STATE_H
#define PLAY_STATE_H

/*==============================================================================================#
|                                                                                               |
| Handmade Lite is an educational game engine, written by Karsten Vermeulen for the purposes of |
| educating other fellow programmers, programming students and anyone else wishing to learn     |
| about game development, C++ and OOP. The engine, class design and overall structure is by no  |
| means perfect and there is certainly room for improvement. Feel free to use, copy, break,     |
| update and do as you wish with this code - it is there, free, for all!                        |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|	                                                                                            |
| Please note, that this project is not open source and therefore has no license affiliated     |
| with it. However, feel free to use the engine to build your own game or learn from the code.  |
| Handmade Lite is an educational tool, designed to be used as such. Please be respectful and   |
| do not distribute the engine or its code as your own work. You may alter or tweak the engine  |
| code as a learning experience and you may also 'borrow' some code and functionality and use   |
| it to create your own game engine or game.                                                    |
|	                                                                                            |
#===============================================================================================#
|                                                                                               |
| If you like Handmade Lite and wish to show your support, if you have any questions about      |
| the project, or if you just want to reach out, please do get in touch:                        |
|																						        |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'PlayState' source files last updated in May 2020   							                |
#==============================================================================================*/

#include <vector>
#include "Background.h"
#include "GameObject.h"
#include "GameState.h"
#include "Cell.h"
#include "Player.h"
#include <Windows.h>
#include <fstream>
#include "Sprite.h"

const int MAX_WIDTH = 20;
const int MAX_HEIGHT = 10;

class Movable;
class PlayState : public GameState
{

public:

	PlayState();
	virtual ~PlayState() {}

public:

	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

public:	//My staff
	std::vector<Cell*> GetAllTiles() { return m_Tiles;  }
	std::vector<Movable*> GetAllMovables() { return Movables;  }
	std::vector<Player*> GetAllPlayers() { return Players; }
	bool OpenFile();			//Check if the file is opened successfuly
	std::vector<Player*> GetPlayerVector() { return Players;  }
	void AddMovable( Movable& moveable) { Movables.push_back(&moveable); }
	void SetPlayer(int player, Player& playerObject);
private:
	Background* m_image;
	std::vector<GameObject*> m_gameObjects;
	//My staff
	void LoadLevel(const std::string& fileName);			//Load the Level from the file (Actually Gets the string)

	std::string m_level;		//The current level Loaded
	//The two Players *Only the player one is Playeable from this app
	Player* m_Player1;
	Player* m_Player2;

	 std::vector<Movable*> Movables;  //Store all the movables here
	std::vector<Player*> Players;	//Vector for storing the Players
	std::vector<Cell*> m_Tiles;		//Vector Storing All the tiles
};

#endif