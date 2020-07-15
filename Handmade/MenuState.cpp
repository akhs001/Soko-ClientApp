#include <time.h>
#include "Input.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
MenuState::MenuState()
{
	m_menu = nullptr;
	//m_image = nullptr;
	
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
		//Load Images
		for (int i = 0; i < 33; i++)
		{
			std::string name = std::to_string(i) + ".png";
			std::string filename = "Assets/mapImages/Decor_Tiles/" + name;
			Sprite::Load(filename, std::to_string(i));
		}
		//load font resource into memory
		Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
		isStaffLoaded = true;
	}

	m_menu = new MainMenu;
	m_menu->SetMenuText("Play game");
	m_menu->SetMenuText("Quit game");

	
	//seed the random number generator
	srand(static_cast<unsigned int>(time(0)));

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that waits for a key to be pressed before transitioning to a different state
//------------------------------------------------------------------------------------------------------
GameState* MenuState::Update(int deltaTime)
{

	//play the background music associated with the image
	//when the state transitions to the next state stop it
	//m_image->PlayMusic();

	//update the main menu to determine which menu choice was made
	m_menu->Update(deltaTime);

	//if player chose to play game, go into main playing state 
	if (m_menu->GetMenuOption() == static_cast<int>(MenuOption::PLAY))
	{
		//m_image->StopMusic();
		return new PlayState;
	}

	//if player chose to exit the game then quit altogether
	if (m_menu->GetMenuOption() == static_cast<int>(MenuOption::QUIT))
	{
		//m_image->StopMusic();
		return nullptr;
	}

	//otherwise return reference to self
	//so that we stay in this game state
	return this;

}
//------------------------------------------------------------------------------------------------------
//function that renders the background splash image and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::Draw()
{

	//m_image->Draw();
	m_menu->Draw();
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object and menu from memory
//------------------------------------------------------------------------------------------------------
void MenuState::OnExit()
{
	//delete m_image;
	delete m_menu;

}

