#include <time.h>
#include "Input.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
#include "Button.h"
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------



MenuState::MenuState()
{
	m_GameStart = false;
	bg = nullptr;
	btn_SinglePlayer = nullptr;
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
		Sound::Load("Assets/Sounds/click.wav", "_CLICK");

		//Load Images
		for (int i = 0; i < 33; i++)
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

	btn_SinglePlayer = new Button(10, 100, Vector2(300, 150), "Single Player", "BUTTON");
	btn_SinglePlayer->SetMenuState(this);

	//seed the random number generator
	srand(static_cast<unsigned int>(time(0)));

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that waits for a key to be pressed before transitioning to a different state
//------------------------------------------------------------------------------------------------------
GameState* MenuState::Update(int deltaTime)
{
	if (m_GameStart)
	{
		return new PlayState();
	}

	bg->Update(1);


	btn_SinglePlayer->Update(1);


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

	btn_SinglePlayer->Draw();
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object and menu from memory
//------------------------------------------------------------------------------------------------------
void MenuState::OnExit()
{
	delete bg;
	delete btn_SinglePlayer;

}

