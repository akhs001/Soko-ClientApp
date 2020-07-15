#include "Input.h"
#include "MainMenu.h"
#include "Screen.h"

//------------------------------------------------------------------------------------------------------
//constructor that loads and links resources, and sets up the main menu text defaults
//------------------------------------------------------------------------------------------------------
MainMenu::MainMenu()
{

	//set default menu choices
	m_menuOptionActive = 0;
	m_menuOptionChoice = -1;



}
//------------------------------------------------------------------------------------------------------
//getter function that returns main menu choice made
//------------------------------------------------------------------------------------------------------
int MainMenu::GetMenuOption() const
{

	return m_menuOptionChoice;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns properties of menu text objects
//here we create temporary 'Text' objects with white text and
//add them into the menu's vector container. Copies are being
//made here so therefore the 'Text' class' copy ctor will be effective
//------------------------------------------------------------------------------------------------------
void MainMenu::SetMenuText(const std::string& text)
{

	Text menuText;
	
	menuText.SetFont("Menu_Font");
	menuText.SetColor(255, 255, 255);
	menuText.SetSize(text.size() * MENU_TEXT_CHAR_W, MENU_TEXT_CHAR_H);
	menuText.SetText(text);
	m_menuText.push_back(menuText);

}
//------------------------------------------------------------------------------------------------------
//function that updates the main menu text on screen
//------------------------------------------------------------------------------------------------------
void MainMenu::Update(int deltaTime)
{

	//flag to monitor if key is pressed so that when pressing UP/DOWN
	//key the selected menu option doesn't move at lightning speed
	static bool isKeyPressed = false;

	//only if DOWN arrow key is pressed and key was not pressed before move 1 option down the menu
	//also check if the last menu item has been reached, which means we need to loop back to the top
	if (Input::Instance()->IsKeyPressed(HM_KEY_DOWN) && !isKeyPressed)
	{
		
		if (m_menuOptionActive == m_menuText.size() - 1)
		{
			m_menuOptionActive = 0;
		}
		
		else
		{
			m_menuOptionActive++;
		}

	}

	//only if UP arrow key is pressed and key was not pressed before move 1 option up the menu
	//also check if the first menu item has been reached, which means we need to go to the bottom
	if (Input::Instance()->IsKeyPressed(HM_KEY_UP) && !isKeyPressed)
	{

		if (m_menuOptionActive == 0)
		{
			m_menuOptionActive = m_menuText.size() - 1;
		}

		else
		{
			m_menuOptionActive--;
		}

	}

	//if ENTER key is pressed assign menu item as choice made 
	if (Input::Instance()->IsKeyPressed(HM_KEY_RETURN))
	{
		m_menuOptionChoice = m_menuOptionActive;
	}

	//update state of key based on if it's pressed or not which will make sure the next time
	//the frame is called the above code will either move the menu option or keep it still
	isKeyPressed = Input::Instance()->IsKeyPressed();

	//loop through all menu items and set their initial color to white
	for (size_t i = 0; i < m_menuText.size(); i++)
	{
		m_menuText[i].SetColor(255, 255, 255);
	}

	//only set the active menu item to a red color
	m_menuText[m_menuOptionActive].SetColor(240, 0, 0);

}
//------------------------------------------------------------------------------------------------------
//function that renders the main menu text on screen
//------------------------------------------------------------------------------------------------------
bool MainMenu::Draw()
{

	//first get resolution so that we can set the menu position accordingly
	SDL_Point resolution = Screen::Instance()->GetResolution();

	//this will position the text in the bottom half of the screen, centered in X
	//X - divide screen width in half and subtract half the width of each text
	//Y - divide screen height in quarters and subtract half of the menu's text heights
	int posY = static_cast<int>((resolution.y - resolution.y / 4) - 
		                        (m_menuText.size() / 2 * MENU_TEXT_CHAR_H));

	//loop through all menu items and render them based on a centre position
	for (size_t i = 0; i < m_menuText.size(); i++)
	{
		m_menuText[i].Draw(static_cast<int>((resolution.x / 2) - m_menuText[i].GetSize().x / 2),  //x
			               static_cast<int>(posY + i * MENU_TEXT_CHAR_H));                        //y
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that resets the menu back to its default
//------------------------------------------------------------------------------------------------------
void MainMenu::Reset()
{

	m_menuOptionActive = 0;
	m_menuOptionChoice = -1;

}
//------------------------------------------------------------------------------------------------------
//destructor that unloads all resources from memory
//------------------------------------------------------------------------------------------------------
MainMenu::~MainMenu()
{

	//Text::Unload("Menu_Font");

}