#include <time.h>
#include "Input.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
#include "Button.h"
#include "Sound.h"
#include <filesystem>
#include <string>

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------

namespace fs = std::filesystem;

MenuState::MenuState()
{
	isQuitPressed = false;
	m_GameStart = false;
	bg = nullptr;
	btn_SinglePlayer = nullptr;
	btn_MultiPlayer = nullptr;
}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object and menu
//------------------------------------------------------------------------------------------------------
static bool isStaffLoaded = false;

bool MenuState::OnEnter()
{


	//Load Background
	bg = new Background("Assets/Images/BG/bg.png");
	
	//Load All staff here
	if (!isStaffLoaded)
	{
		Sound::Load("Assets/Sounds/click.mp3", "CLICK");
		Sound::Load("Assets/Sounds/wrongMove.wav", "WRONG");
		Sound::Load("Assets/Sounds/PlayerMove.wav", "P_MOVE");
		//Load Images
		for (int i = 0; i < 45; i++)
		{
			std::string name = std::to_string(i) + ".png";
			std::string filename = "Assets/mapImages/Decor_Tiles/" + name;
			Sprite::Load(filename, std::to_string(i));
		}
		//load font resource into memory
		Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
		Text::Load("Assets/Fonts/Impact.ttf", "FONT", Text::FontSize::SMALL);
		isStaffLoaded = true;

	}

	btn_SinglePlayer = new Button(10, 50, Vector2(300, 150), "Single Player", "BUTTON",false);
	btn_SinglePlayer->SetMenuState(this);

	btn_MultiPlayer = new Button(10, 200, Vector2(300, 150), "MultiPlayer", "BUTTON",false);
	btn_MultiPlayer->SetMenuState(this);

	btn_Quit = new Button(10, 350, Vector2(300, 150), "Exit", "BUTTON",false);
	btn_Quit->SetMenuState(this);
	//seed the random number generator
	srand(static_cast<unsigned int>(time(0)));



	return true;

}
//------------------------------------------------------------------------------------------------------
//function that waits for a key to be pressed before transitioning to a different state
//------------------------------------------------------------------------------------------------------
GameState* MenuState::Update(int deltaTime)
{
	if (isQuitPressed)
	{
		return nullptr;
	}

	if (m_GameStart)
	{
		if (FILENAME == "")
		{
			m_GameStart = false;
			return new PlayState();
		}
		else
		{
			m_GameStart = false;
			return new PlayState(FILENAME);
		}

	}

	for (Button* b : LevelBtns)
	{
		b->Update(1);
	}
	bg->Update(1);


	btn_SinglePlayer->Update(1);
	btn_MultiPlayer->Update(1);
	btn_Quit->Update(1);

	//otherwise return reference to self
	//so that we stay in this game state
	return this;

}
//------------------------------------------------------------------------------------------------------
//function that renders the background splash image and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::Draw()
{
	bg->Draw();

	for (Button* b : LevelBtns)
	{
		b->Draw();
	}

	btn_SinglePlayer->Draw();
	btn_MultiPlayer->Draw();
	btn_Quit->Draw();
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object and menu from memory
//------------------------------------------------------------------------------------------------------
void MenuState::OnExit()
{
	delete bg;
	delete btn_SinglePlayer;
	delete btn_MultiPlayer;
	delete btn_Quit;
}

void MenuState::ShowLevels()
{
	CheckforLevels();
}

void MenuState::StartGame(std::string level)
{
	FILENAME = level;
	m_GameStart = true;
}

void MenuState::CheckforLevels()
{
	std::string LevelPath = "Assets/Levels/";
	int c = 1;
	for (const auto& entry : fs::directory_iterator(LevelPath))
	{
		std::string name = entry.path().filename().string();

		Button* b = new Button(250 , (c *20), Vector2( 200 , 20), name , "BUTTON" , true);
		b->SetMenuState(this);
		LevelBtns.push_back(b);
		c+=1;
	}

}

