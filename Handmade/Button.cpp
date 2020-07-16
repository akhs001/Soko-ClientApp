#include "Button.h"
#include "Text.h"
#include "Input.h"
#include <iostream>
#include "Utils.h"
#include "MenuState.h"


static bool isfONTLoaded = false;
int currentBoardSize = 0;



Button::Button(int  x,int  y , Vector2 size, const std::string& text ,const std::string& ID)
{
	m_state = nullptr;
	m_canClick = true;
	m_ID = ID;

	//Position
	m_pos = Vector2(x, y);
	//Size
	m_size = Vector2(size.GetX(), size.GetY());
	//Image
	m_image.SetSpriteDimension(m_size.GetX(), m_size.GetY());
	m_image.SetImageDimension(1,1,256 ,256);
	m_image.SetImage(m_ID);
	//Text
	m_text.SetFont("FONT");
	m_text.SetColor(200, 100, 50);
	m_text.SetSize(m_size.GetX()/2, m_size.GetY()/2);
	m_text.SetText(text);
	//Collider
	m_collider.SetDimension(m_size.GetX(), m_size.GetY());
	m_collider.SetPosition((int)x,(int)y);
	m_click.SetSound("CLICK");
}

Button::~Button()
{
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
		m_click.Play();
		m_canClick = false;
		//If we click exit
		if (m_text.GetText() == "Single Player")
		{
			m_state->StartGame();
			return;
		}

	}
}

bool Button::Draw()
{
	m_image.Draw(m_pos.GetX(),m_pos.GetY());
	m_text.Draw(m_pos.GetX() + m_size.GetX()/4, m_pos.GetY() + m_size.GetY()/3);
	return true;
}

bool Button::isClicked()
{
	if (Input::Instance()->IsMouseClicked())
	{
	
		//Check if the click is on pthe button
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

void Button::SetMenuState(MenuState* state)
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
//
//Vector2 Button::GetPos()
//{
//	return m_pos;
//}

//MenuState* Button::GetState()
//{
//	return m_state;
//}

//Vector2 Button::GetSize()
//{
//	return m_size;
//}

void Button::SetImage(std::string ImageID)
{
	m_image.SetImage( ImageID);
}




