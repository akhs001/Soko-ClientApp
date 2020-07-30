#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>
#include "GameObject.h"
#include "GameState.h"
#include "Cell.h"
#include "Player.h"
#include <Windows.h>
#include <fstream>
#include "Sprite.h"
#include "TCPConnection.h"
#include <iostream>
#include "TextBox.h"
#include "Dice.h"

//MAXIMUM SIZE OF THE BOARD (SAME AS THE EDITOR)
const int MAX_WIDTH = 50;
const int MAX_HEIGHT = 50;
//*********************************************

//Forward declarations
class Button;
class Movable;
//********************

class PlayState : public GameState
{
public:
	PlayState(std::string file, bool Multiplayer, std::vector<LevelData> SavedData , int current);
	virtual ~PlayState() {}

public:
	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

public:	//My staff
	std::vector<Cell*> GetAllTiles();
	std::vector<Movable*> GetAllMovables();
	std::vector<Player*> GetAllPlayers();


	void SetPlayer(int player, Player& playerObject);
	void SetFileName(std::string fileName);
	void AddMovable(Movable& moveable);
	void CheckIfComplete();
	bool IsMultiPlayer();
	bool IsGameRunning;
	bool IsGaneStarted();
	bool OpenFile();													//Check if the file is opened successfuly

	virtual void StartGame( std::string fileName , int level);			//Load the Level from the file 
	virtual void StartGameS(std::string data);							//Load the Level from the Data
	virtual std::string GetFilename();
	virtual void GoBack();

	void SaveData(std::vector<LevelData>& data);
	void MoveBallOutOfPlace();
	void AddBallInPlace();
	int GetBallsOnPlace();
	int GetCurrentLevel();
	int GetTotalBalls();
	int GetTileSize();

	//SYNC MOVEMENTS
	void UpdateMovables();
	void UpdateMovables(std::string Data);

	void UpdatePlayer();
	void UpdateServerPosition(std::string Data);

private:
	Sprite Background;
	//My staff
    int tileS;						//The tilesize
	int currentLevel;
	int TotalBalls;					//Returns How many Balls the current level have
	int BallsOnPlace;				//Returns How many balls are Placed

	bool isLevelComplete;
	bool isBackPressed;
	bool m_isMultiplayer;

	char filename[MAX_PATH];	//char array for storing the filePath
	std::string m_level;		//The current level Loaded
	//The two Players *Only the player one is Playeable from this app
	Player* m_Player1;
	Player* m_Player2;
	 std::vector<Movable*> Movables;  //Store all the movables here
	std::vector<Player*> Players;	//Vector for storing the Players
	std::vector<Cell*> m_Tiles;		//Vector Storing All the tiles
	Button* btn_Back;
	Button* btn_Reset;
	TCPConnection* m_Client;
	bool isGameStarted;
	bool connectionProblem;
	//Levels 
	std::vector<LevelData> m_levels;
	std::vector<TextBox*> m_texts;
	TextBox* t;
	float m_timeToStart;

	Dice* m_myDice;

};

#endif