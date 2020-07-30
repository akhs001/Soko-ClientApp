#include "Button.h"
#include "Sound.h"
#include "Text.h"
#include "Input.h"
#include <iostream>
#include "Utils.h"
#include "MenuState.h"

static bool isLoaded = false;
int currentBoardSize = 0;


Button::Button(int  x,int  y , Vector2::vector2 size, const std::string& text ,const std::string& ID , bool isLevel)
{
	if (!isLoaded)
	{
		Sprite::Load("Assets/level_select/bg.png", "BUTTON");
		isLoaded = true;
	}
	isTooltip = false;
	m_tooltip = nullptr;
	//If the button is Level
	IsLevel(isLevel);
	//The State that the button is
	m_state = nullptr;
	m_canClick = true;
	m_ID = ID;
	//The position
	m_pos = Vector2::vector2({ x, y });
	//The size
	m_size = Vector2::vector2({ size.x, size.y });

	//Image
	m_image.SetSpriteDimension(size.x, size.y);
	if (ID == "BUTTON")
	{
		m_image.SetImageDimension(1, 1, 1307, 1457);
	}

	m_image.SetImage("BUTTON");
	//Text
	m_text.SetFont("FONT");
	if (isLevel)		//If is level the button is different
	{
		m_text.SetColor(5, 20, 50);
		m_text.SetSize(size.x / 2, size.y / 2);
		m_text.SetText(text);
	}
	else
	{
		m_text.SetColor(100, 100, 50);
		m_text.SetSize(size.x / 2, size.y / 2);
		m_text.SetText(text);
	}

	//Collider
	m_collider.SetDimension(size.x, size.y);
	m_collider.SetPosition((int)x, (int)y);
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

	if (isHover() && !isTooltip && m_isLevel)
	{
		std::string file;
		//Create 'the path
		file = "Assets/Levels/SinglePlayer/" + m_levelAssigned;
		file = file.substr(0, file.length() - 3);
		file += "png";
		std::cout << file << std::endl;
		m_tooltip = new ToolTip(file);
		isTooltip = true;
	}
	else if (!isHover())
	{
		m_tooltip = nullptr;
		isTooltip = false;
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
			std::string fileLevel = "Assets/Levels/SinglePlayer/" + m_levelAssigned;
			//And open the level
			m_state->StartGame(fileLevel ,std::stoi( m_text.GetText()) );
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
			m_state->StartGame(m_state->GetFilename() , m_state->GetCurrentLevel());
			return;
		}
	}
}

bool Button::isHover()
{
	//Check if the click is on the button
	int xp = Input::Instance()->GetMousePosition().x;
	int yp = Input::Instance()->GetMousePosition().y;

	AABB m_temp;
	m_temp.SetPosition(xp, yp);
	return m_collider.IsColliding(m_temp);

}

bool Button::Draw()
{
	m_image.Draw(m_pos.x,m_pos.y);									//Draw Image
	m_text.Draw(m_pos.x + m_size.x/4, m_pos.y + m_size.y/3);		//Draw Text

	if (m_tooltip)
	{
		m_tooltip->Draw();
	}
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

void Button::SetPos(Vector2::vector2 pos)
{
	m_pos = pos;
	m_collider.SetPosition(pos.x, pos.y);
}

Vector2::vector2 Button::GetPos()
{
	return m_pos;
}

GameState* Button::GetState()
{
	return m_state;
}

Vector2::vector2 Button::GetSize()
{
	return m_size;
}

void Button::SetImage(std::string ImageID)
{
	m_image.SetImage( ImageID);
}




