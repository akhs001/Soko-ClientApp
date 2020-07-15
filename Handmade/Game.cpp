#include "Game.h"
#include "Input.h"
#include "MenuState.h"
#include "Screen.h"
#include "Text.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Game::Game(GameState* initialGameState)
{

	m_deltaTime = 0;
	m_gameState = initialGameState;

}
//------------------------------------------------------------------------------------------------------
//function that initializes all sub-systems of the game
//------------------------------------------------------------------------------------------------------
bool Game::Initialize(const std::string& name, int screenWidth, int screenHeight, bool fullscreen)
{

	//initialise game screen with passed values and return false if error occured
	if (!Screen::Instance()->Initialize(name.c_str(), screenWidth, screenHeight, fullscreen))
	{
		return false;
	}

	//set the background rendering color
	Screen::Instance()->SetClearColor(100, 149, 237);

	//initialize audio sub-system and return false if error occured
	if (!(Music::Initialize()))
	{
		//not serious - game does not need to end
		//add your own outcome/messages here...
	}

	//initialize font sub-system and return false if error occured
	if (!Text::Initialize())
	{
		//not serious - game does not need to end
		//add your own outcome/messages here...
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that runs the main game loop and updates all components
//------------------------------------------------------------------------------------------------------
bool Game::Run()
{

	//load up all of the initial game state objects
	m_gameState->OnEnter();

	//update and render all objects while the current state is valid
	//each state will return a pointer to itself, a new game state or null
	//once the state is null, this loop will end, thereby ending the game
	while (m_gameState)
	{

		//save time value to mark the start of the frame
		int startTime = SDL_GetTicks();

		//update screen by clearing SDL frame buffer
		Screen::Instance()->Update();

		//update input handling by listening for input events
		Input::Instance()->Update();

		//update the currently active state
		//store the returned game state to 
		//determine if we need to change states
		GameState* nextState = m_gameState->Update(m_deltaTime);

		//render the currently active state
		m_gameState->Draw();
			
		//swap the frame buffer
		Screen::Instance()->Draw();

		//if the returned game state is different to our
		//current state then we need to make a change
		//we exit the old and only enter the new if not null
		if (nextState != m_gameState)
		{
			m_gameState->OnExit();
			delete m_gameState;
			m_gameState = nextState;

			if (m_gameState)
			{
				m_gameState->OnEnter();
			}
		}

		//calculate time value passed for one frame call
		//if vsync is on this value should be around 16ms
		m_deltaTime = SDL_GetTicks() - startTime;
			
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down all sub-systems of the game
//------------------------------------------------------------------------------------------------------
void Game::ShutDown()
{

	//close down font and audio sub-systems
	Text::ShutDown();
	Music::ShutDown();

	//close down game screen 
	Screen::Instance()->ShutDown();

}