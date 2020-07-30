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
#include "Screen.h"


//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------

namespace fs = std::filesystem;

MenuState::MenuState()
{
	for (int i = 0; i < 20; i++)
	{
		m_levels.push_back(LevelData{ i , false });
	}
	LoadData(m_levels);
	isQuitPressed = false;
	m_GameStart = false;



	btn_SinglePlayer = nullptr;
	btn_MultiPlayer = nullptr;
}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object and menu
//------------------------------------------------------------------------------------------------------
static bool isStaffLoaded = false;




bool MenuState::OnEnter()
{

	//Load All staff here
	if (!isStaffLoaded)
	{
		Sprite::Load("Assets/Images/start_1.png", "STAR");
		Sound::Load("Assets/Sounds/click.wav", "CLICK");
		Sound::Load("Assets/Sounds/wrongMove.wav", "WRONG");
		Sound::Load("Assets/Sounds/PlayerMove.wav", "P_MOVE");

		Sprite::Load("Assets/Images/BG/bg.png", "BACK");
		//load font resource into memory
		Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
		Text::Load("Assets/Fonts/Impact.ttf", "FONT", Text::FontSize::SMALL);
		isStaffLoaded = true;

	}

	Background.SetImageDimension(1, 1, 1921, 1080);
	Background.SetSpriteDimension(Screen::Instance()->GetResolution().x, Screen::Instance()->GetResolution().y);
	Background.SetImage("BACK");

	btn_SinglePlayer = new Button(10, 50, Vector2::vector2({ 300, 150 }), "Single Player", "BUTTON", false);
	btn_SinglePlayer->SetMenuState(this);

	btn_MultiPlayer = new Button(10, 200, Vector2::vector2({ 300, 150 }), "MultiPlayer", "BUTTON", false);
	btn_MultiPlayer->SetMenuState(this);

	btn_Quit = new Button(10, 350, Vector2::vector2({ 300, 150 }), "Exit", "BUTTON", false);
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
		m_GameStart = false;
		return new PlayState(FILENAME , m_isMultiplayer , m_levels , currentLevel);

	}

	for (Button* b : LevelBtns)
	{
		b->Update(1);
	}


	btn_SinglePlayer->Update(1);
	btn_MultiPlayer->Update(1);
	btn_Quit->Update(1);

	//otherwise return reference to self
	//so that we stay in this game state
	return this;

}

void MenuState::LoadData(std::vector<LevelData>& data)
{
	std::ifstream file("Save.dat", std::ios_base::in | std::ios_base::binary);

	if (file.fail())
	{
		std::cout << "Save Data file not exist" << std::endl;
		std::ofstream f("Save.dat", std::ios_base::out | std::ios_base::binary);

		//Init the file
		int i;
		for ( i = 0; i < 20; i++)
		{
			data.push_back(LevelData({ i , 0 }));
		}

		for ( i = 0; i < 20; i++)
		{
			f.write((char*)&data[i].level, sizeof(int));
			f.write((char*)&data[i].isPassed, sizeof(int));
		}
		
		std::cout << "New save file has Created" << std::endl;

		f.close();

		return;
	}
	else
	{
		//Print the data

		for (int i = 0; i < 20; i++)
		{
			file.read((char*)&data[i].level, sizeof(int));
			file.read((char*)&data[i].isPassed, sizeof(int));
			std::cout << data[i].level << ":" << data[i].isPassed << std::endl;
		}


		file.close();
		std::cout << "Data Loaded" << std::endl;
	}
}



//------------------------------------------------------------------------------------------------------
//function that renders the background splash image and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::Draw()
{
	Background.Draw();

	for (Button* b : LevelBtns)
	{
		b->Draw();
	}

	for (star* s : m_stars)
	{
		s->Draw();
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
	delete btn_SinglePlayer;
	delete btn_MultiPlayer;
	delete btn_Quit;

	for (star* s : m_stars)
	{
		delete s;
	}
	isStaffLoaded = false;

	//UnLoad All staff here

		Sprite::Unload( "STAR");
		Sound::Unload( "CLICK");
		Sound::Unload("WRONG");
		Sound::Unload( "P_MOVE");

		Sprite::Unload("BACK");

		Text::Unload( "Menu_Font");
		Text::Unload( "FONT");
		isStaffLoaded = false;

}

void MenuState::ShowLevels()
{
	CheckforLevels();
}


void MenuState::StartGame()
{
	m_GameStart = true;
}

void MenuState::StartGame(std::string level , int levelNumber)
{
	currentLevel = levelNumber;
	FILENAME = level;
	m_GameStart = true;
}



void MenuState::CheckforLevels()
{
	m_stars.clear();
	//Clear previous level buttons
	LevelBtns.clear();

	std::string LevelPath = "";
	LevelPath = "Assets/Levels/SinglePlayer/";

	int c = 0;
	for (const auto& entry : fs::directory_iterator(LevelPath))
	{
		std::string name = entry.path().filename().string();
		if (name.substr(name.length() - 3, name.length()) == "bin")
		{
			Button* b = new Button(0, 0, Vector2::vector2({ 50 , 50 }), std::to_string(c+1), "BUTTON", true);
			b->SetMenuState(this);
			b->SetLevel(name);
			LevelBtns.push_back(b);
			c += 1;
		

		}

	}
	int rows = 10;
	int _width = Screen::Instance()->GetResolution().x;
	int _height = Screen::Instance()->GetResolution().y;

	int  middleX = _width * 0.5f - (50 * rows * 0.5f);
	int  middleY = _height * 0.5f - (50 * rows * 0.5f);
	c = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (c > LevelBtns.size() - 1) { break; }
			LevelBtns[c]->SetPos({ middleX + j * 50,middleY + i * 50 });


			//Check if the level is already passed and draw a star
			if (m_levels[c].isPassed == 1)
			{
				//Create a star
				star* newStar = new star({ middleX + j * 50 , middleY + i * 50 }, "Assets/Images/star_1.png");
				m_stars.push_back(newStar);

			}
			c++;
		}
	}
}

