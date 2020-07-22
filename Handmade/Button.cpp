#include "Button.h"
#include "Sound.h"
#include "Text.h"
#include "Input.h"
#include <iostream>
#include "Utils.h"
#include "MenuState.h"

static bool isLoaded = false;
int currentBoardSize = 0;


Button::Button(int  x,int  y , Vector2 size, const std::string& text ,const std::string& ID , bool isLevel)
{
	if (!isLoaded)
	{
		Sprite::Load("Assets/level_select/bg.png", "BUTTON");
		isLoaded = true;
	}
	//If the button is Level
	IsLevel(isLevel);
	//The State that the button is
	m_state = nullptr;
	m_canClick = true;
	m_ID = ID;
	//The position
	m_pos = Vector2(x, y);
	//The size
	m_size = Vector2(size.GetX(), size.GetY());

	//Image
	m_image.SetSpriteDimension(m_size.GetX(), m_size.GetY());
	if (ID == "BUTTON")
	{
		m_image.SetImageDimension(1, 1, 1307, 1457);
	}
	m_image.SetImage(m_ID);
	//Text
	m_text.SetFont("FONT");
	if (isLevel)		//If is level the button is different
	{
		m_text.SetColor(5, 20, 50);
		m_text.SetSize(m_size.GetX()/2, m_size.GetY()/2);
		m_text.SetText(text);
	}
	else
	{
		m_text.SetColor(100, 100, 50);
		m_text.SetSize(m_size.GetX()/2, m_size.GetY()/2);
		m_text.SetText(text);
	}

	//Collider
	m_collider.SetDimension(m_size.GetX(), m_size.GetY());
	m_collider.SetPosition((int)x,(int)y);
	m_click.SetSound("CLICK");
}

Button::~Button()
{
	isLoaded = false;
	Sprite::Unload(m_ID);
}

float ctr = 0.0f;
void Button::Update(int deltaTime)
{
	if (!m_canClick)
	{
		ctr += 0.1f ;
	}

	if (ctr > 2.0f)
	{
		m_canClick = true;
		ctr = 0.0f;
	}

	if (!m_canClick) { return; }

	//The function bellow check if the mouse is clicked and get the Name on the Button
	//After we do the action for this button
	if (isClicked())
	{
		m_click.Play();	//Playe the click sound
		m_canClick = false;

		//If we click a level
		if (IsLevel())
		{
			//Create the path
			std::string fileLevel = "Assets/Levels/" + m_levelAssigned;
			//And open the level
			m_state->StartGame(fileLevel);
			return;
		}

		//If we click Single Player Game
		if (m_text.GetText() == "Single Player")
		{
			m_state->IsMultiPlayer(false);
			m_state->ShowLevels();
			return;
		}
		//If we click Single Player Game
		if (m_text.GetText() == "MultiPlayer")
		{
			m_state->IsMultiPlayer(true);
			m_state->StartGame();
			return;
		}
		//if we press back
		if (m_text.GetText() == "BACK")
		{
			m_state->GoBack();
			return;
		}
		//if we press exit
		if (m_text.GetText() == "Exit")
		{
			m_state->Quit();
			return;
		}
		//if we press reset
		if (m_text.GetText() == "RESET")
		{
			m_state->StartGame(m_state->GetFilename());
			return;
		}
	}
}

bool Button::Draw()
{
	m_image.Draw(m_pos.GetX(),m_pos.GetY());											//Draw Image
	m_text.Draw(m_pos.GetX() + m_size.GetX()/4, m_pos.GetY() + m_size.GetY()/3);		//Draw Text
	return true;
}

/// <summary>
/// Check if the mouse is clicked
/// </summary>
/// <returns></returns>
bool Button::isClicked()
{
	if (Input::Instance()->IsMouseClicked())
	{
		//Check if the click is on the button
		int xp = Input::Instance()->GetMousePosition().x;
		int yp = Input::Instance()->GetMousePosition().y;

		AABB m_temp;
		m_temp.SetPosition(xp, yp);
		return m_collider.IsColliding(m_temp);
	}
	return false;
}

bool Button::CanClick()
{
	return m_canClick;
}

void Button::SetColor(int color)
{
	m_color = color;
}

void Button::SetMenuState(GameState* state)
{
	m_state = state;
}

void Button::CanClick(bool flag)
{
	m_canClick = flag;
}

int Button::GetColor()
{
	return m_color;
}

void Button::SetPos(Vector2 pos)
{
	m_pos = pos;
	m_collider.SetPosition(pos.GetX(), pos.GetY());
}

Vector2 Button::GetPos()
{
	return m_pos;
}

GameState* Button::GetState()
{
	return m_state;
}

Vector2 Button::GetSize()
{
	return m_size;
}

void Button::SetImage(std::string ImageID)
{
	m_image.SetImage( ImageID);
}




