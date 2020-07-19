#include "Player.h"
#include "Input.h"
#include <iostream>
#include <vector>
#include "PlayState.h"
#include <string>
#include "Movable.h"

Movement PlayerMove;

Player::Player(int x, int y,int size,  std::string ID)
{
	m_canControl = false;
	m_state = NULL;
	m_canMove = true;
	m_position.x = x;
	m_position.y = y;
	m_size.x = size;
	m_size.y = size;

	m_image.SetImageDimension(1, 1, IMAGE_SIZE, IMAGE_SIZE);
	m_image.SetSpriteDimension(m_size.x , m_size.y);
	m_image.SetImage(ID);

	m_collider.SetDimension(size, size);
	m_collider.SetPosition(m_position.x, m_position.y);

	m_WalkSnd.SetSound("P_MOVE");
	m_WrongMove.SetSound("WRONG");

}



Player::~Player()
{
	m_image.Unload();
}


//Return true if you can move or false if cant
bool Player::CheckCollision()
{
	std::vector<Cell*> allcells = m_state->GetAllTiles();	//Get All Tiles from the PlayState
	
	std::vector<Movable*> allMovables = m_state->GetAllMovables();

	std::vector<Player*> allPlayers = m_state->GetAllPlayers();

//Loop and check Movables
	for (Movable* m : allMovables)
	{
		if (m_collider.IsColliding(m->GetCollider()))
		{
			if (m->CanMove(PlayerMove)) //If the Movable Object can move to the direction of player
			{
				m->Move(PlayerMove, GetSize()); //Move
			}
			else
			{
				return false;
			}
		}
	}
	
	//Check for collision with otherplayer
	for (Player* p : allPlayers)
	{
		if (p != this &&  m_collider.IsColliding(p->GetCollider()))
		{
			return false;
		}
	}

	for (Cell* c : allcells)
	{
		if (m_collider.IsColliding(c->GetCollider()))
		{
				//Check if c is passable or not
			int numCell = c->GetTile();
			
			return c->IsWalkable();
		}
	}
	return true;
}

float cnt = 0.0f;
void Player::Update(int deltaTime)
{
	if (!IsControllable()) { return;  } //If this not my Player return

	///****Just a counter to Prevent continues moving*****
	if (cnt < 1.0f && !m_canMove)
	{
		cnt += 0.1f;
		if (cnt >= 1.0f)
		{
			m_canMove = true;
		}
		return;
	}
	cnt = 0.0f;
	///****************************************************

	//CHECK INPUT
	if (Input::Instance()->IsKeyPressed(HM_KEY_LEFT))
	{
				//Move the Collider
		m_collider.SetPosition(m_position.x- GetSize(), m_position.y);
		PlayerMove = LEFT;
		//Check all the tiles for collision
		if (CheckCollision())	//If we can move
		{
			//Move the Player
			m_WalkSnd.Play();
			m_position.x -= GetSize();
			m_canMove = false;
		}
		else					//If we cant move
		{
			m_collider.SetPosition(m_position.x, m_position.y);
			//Return back the collider
			m_WrongMove.Play();
			m_canMove = false;
		}
	}
	else if (Input::Instance()->IsKeyPressed(HM_KEY_RIGHT))
	{
		m_collider.SetPosition(m_position.x + GetSize(), m_position.y);
		PlayerMove = RIGHT;
		if (CheckCollision())
		{
			m_WalkSnd.Play();
			m_position.x += GetSize();
			m_canMove = false;
		}
		else
		{
			//Return back the collider
			m_collider.SetPosition(m_position.x, m_position.y);
			m_WrongMove.Play();
			m_canMove = false;
		}

	}
	else if (Input::Instance()->IsKeyPressed(HM_KEY_UP))
	{
		m_collider.SetPosition(m_position.x, m_position.y - GetSize());
		PlayerMove = UP;
		if (CheckCollision())
		{
			m_WalkSnd.Play();
			m_position.y -= GetSize();
			m_canMove = false;
		}
		else
		{
			//Return back the collider
			m_collider.SetPosition(m_position.x, m_position.y);
			m_WrongMove.Play();
			m_canMove = false;
		}

	}
	else if (Input::Instance()->IsKeyPressed(HM_KEY_DOWN))
	{
		m_collider.SetPosition(m_position.x, m_position.y + GetSize());
		PlayerMove = DOWN;
		if (CheckCollision())
		{
			m_WalkSnd.Play();
			m_position.y += GetSize();
			m_canMove = false;
		}
		else
		{
			//Return back the collider
			m_collider.SetPosition(m_position.x, m_position.y);
			m_WrongMove.Play();
			m_canMove = false;
		}
	}
}

bool Player::Draw()
{
	m_image.Draw(m_position.x, m_position.y);
    return true;
}





