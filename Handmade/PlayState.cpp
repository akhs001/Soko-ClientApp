#include "EndState.h"
#include "Game.h"
#include "Input.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Utils.h"
#include "Sprite.h"
#include "Screen.h"
#include "Player.h"
#include "Movable.h"

char filename[MAX_PATH];	//char array for storing the filePath



PlayState::PlayState()
{
	m_gridMaker = nullptr;
	m_Player1 = nullptr;
	m_Player2 = nullptr;
	m_level = "";
	m_image = nullptr;
}
//------------------------------------------------------------------------------------------------------
//function that creates all game objects for the state
//------------------------------------------------------------------------------------------------------
bool PlayState::OnEnter()
{
	m_gridMaker = new GridMaker(this);

	m_image = new Background("Assets/Images/Play_1280x720.png", "Assets/Music/Play.ogg");

	//On enter Ask for Level File to open
	if (!OpenFile())
	{
		MessageBox(0, "Wrong LevelFile", "Wrong Level", MB_OK);
	}
	else
	{
		m_level = LoadLevel(filename);		//Get the level from the file
		std::vector<std::string> levelData;		//vector to store all the data tiles from the level
		levelData = Utils::Split(m_level, ',');		//Use my function Split to split the one string into chunks
		//Check if the level is correct
		if (levelData.size() > 25)
		{
			int m_levelWidth = std::stoi(levelData[0]);				//Get the level width
			int m_levelHeight = std::stoi(levelData[1]);			//Get the level height

			//CreateLevel(m_levelWidth, m_levelHeight, levelData);	//Create the level
			m_gridMaker->CreateLevel(m_Tiles,  m_levelWidth, m_levelHeight, levelData);
		}
		else
		{
			MessageBox(0, "Wrong LevelFile", "Wrong Level", MB_OK);
		}
	}
	return true;
}
//------------------------------------------------------------------------------------------------------
//function that reads key presses, mouse clicks and updates all game objects in scene
//------------------------------------------------------------------------------------------------------
GameState* PlayState::Update(int deltaTime)
{
	//Update Players
	for (Player* p : Players)
	{
		if (p != nullptr)
			p->Update(1);
	}

	for (Movable* m : Movables)
	{
		if (m != nullptr)
			m->Update(1);
	}

	for (Cell* c : m_Tiles)
	{
		if (c != nullptr)
			c->Update(1);
	}

	//the M key moves to the main menu
	if (Input::Instance()->IsKeyPressed(HM_KEY_M))
	{
		m_image->StopMusic();
		return new MenuState;
	}

	//the Q key moves to the ending state
	if (Input::Instance()->IsKeyPressed(HM_KEY_Q))
	{
		m_image->StopMusic();
		return new EndState;
	}

	//loop through all game objects in vector and update them only if they are active
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(deltaTime);
		}
	}

	//otherwise return reference to self
	//so that we stay in this game state
	return this;

}
//------------------------------------------------------------------------------------------------------
//function that renders all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Draw()
{
	//render the background image
	m_image->Draw();

	//loop through all game objects in vector and 
	//display them only if they are active and visible
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive() && (*it)->IsVisible())
		{
			(*it)->Draw();
		}
	}

	for (Cell* c : m_Tiles)
	{
		if (c != nullptr)
			c->Draw();
	}


	for (Movable* m : Movables)
	{
		if (m != nullptr)
			m->Draw();
	}

	for (Player* p : Players)
	{
		if (p != nullptr)
			p->Draw();
	}
	
	return true;
}
//------------------------------------------------------------------------------------------------------
//function that removes all game objects from memory
//------------------------------------------------------------------------------------------------------
void PlayState::OnExit()
{
	//loop through all game objects in vector and remove them from memory
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete (*it);
	}

	m_gameObjects.clear();
	m_Tiles.clear();
	delete m_gridMaker;
}

bool PlayState::OpenFile()
{
		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = ("Text Files\0*.txt\0Any File\0*.*\0");
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = ("Select a Level To Play!");
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn))
		{
			std::cout << "File Opened \"" << filename << "\"\n";
			return true;
		}
		else
		{
			std::cout << "Error Opening the file \"" << filename << "\"\n";
			return false;
		}

}


std::string PlayState::LoadLevel(const std::string& fileName)
{
	std::ifstream ifile(fileName);	//Open the file

	std::string data;		//Set the data variable

    std::getline(ifile, data);	//Get the  file Data

	return data;
}

void PlayState::SetPlayer(int player,  Player& playerObject)
{
	switch (player)
	{
	case 1:
		m_Player1 = &playerObject;
		Players.push_back(m_Player1);
		break;
	case 2:
		m_Player2 = &playerObject;
		Players.push_back(m_Player2);
		break;
	}
}

// DEPRECATED -> Moved to GridMaker class
//void PlayState::CreateLevel(int width, int height,const std::vector<std::string>& LevelData)
//{
//}
