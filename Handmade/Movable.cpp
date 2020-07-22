#include "Movable.h"


static bool isSoundLoaded = false;

Movable::Movable(int x, int y,int size, std::string ID)
{
	if(!isSoundLoaded)
	{
		Sound::Load("Assets/Sounds/move.wav", "MOVE_SND");
		Sound::Load("Assets/Sounds/correct.wav", "ONPLACE_SND");

		isSoundLoaded = true;
	}
	m_state = nullptr;
	m_onPlaceSnd.SetSound("ONPLACE_SND");
	m_moveSnd.SetSound("MOVE_SND");
    m_canMove = true;
    m_position.x=(x );
    m_position.y=( y );
    m_size.x= (size);
	m_size.y=(size);
	m_OnPlace = false;
    m_image.SetImageDimension(1, 1, IMAGE_SIZE, IMAGE_SIZE);
    m_image.SetSpriteDimension(m_size.x, m_size.y);
    m_image.SetImage(ID);

    m_collider.SetDimension(size, size);
    m_collider.SetPosition(m_position.x, m_position.y);
}

Movable::~Movable()
{ 
    m_image.Unload();
}

void Movable::Update(int deltaTime)
{
    m_collider.SetPosition(m_position.x, m_position.y);
}

bool Movable::Draw()
{
    m_image.Draw(m_position.x, m_position.y);
    return true;
}

void Movable::Move(Movement movement, int amount)
{
	switch (movement)
	{
	case RIGHT:
		m_moveSnd.Play();
		m_position.x=(m_position.x + amount);
		m_state->UpdateMovables();
		break;
	case LEFT:
		m_moveSnd.Play();
		m_position.x=(m_position.x - amount);
		m_state->UpdateMovables();
		break;
	case UP:
		m_moveSnd.Play();
		m_position.y=(m_position.y - amount);
		m_state->UpdateMovables();
		break;
	case DOWN:
		m_moveSnd.Play();
		m_position.y=(m_position.y + amount);
		m_state->UpdateMovables();
		break;
	default:
		break;
	}
}

/// <summary>
/// Check if the movable can move to this movement
/// </summary>
/// <param name="movement"></param>
/// <returns></returns>
bool Movable::CanMove(Movement movement)
{
	std::vector<Player*> allPlayers = m_state->GetAllPlayers();
	std::vector<Cell*> allCells = m_state->GetAllTiles();
	std::vector<Movable* > allMovables = m_state->GetAllMovables();
	//Check other Players
	for (Player* p : allPlayers)
	{
		switch (movement)
		{
		case LEFT:
			m_collider.SetPosition(m_position.x - GetSize(), m_position.y); //Move the collider left
			if (m_collider.IsColliding(p->GetCollider()))
			{
				return false;
			}

			break;
		case RIGHT:
			m_collider.SetPosition(m_position.x + GetSize(), m_position.y); //Move the collider left
			if (m_collider.IsColliding(p->GetCollider()))
			{
				return false;
			}

			break;
		case UP:
			m_collider.SetPosition(m_position.x, m_position.y - GetSize()); //Move the collider left
			if (m_collider.IsColliding(p->GetCollider()))
			{
				return false;
			}

			break;
		case DOWN:
			m_collider.SetPosition(m_position.x, m_position.y + GetSize()); //Move the collider left
			if (m_collider.IsColliding(p->GetCollider()))
			{
				return false;
			}

			break;
		}
	}
	
	//check other balls
	for (Movable* m : allMovables)
	{
		if (m == this) { continue; }
		switch (movement)
		{
		case LEFT:
			m_collider.SetPosition(m_position.x - GetSize(), m_position.y); //Move the collider left
			if (m_collider.IsColliding(m->GetCollider()))
			{
				return false;
			}

			break;
		case RIGHT:
			m_collider.SetPosition(m_position.x + GetSize(), m_position.y); //Move the collider left
			if (m_collider.IsColliding(m->GetCollider()))
			{
				return false;
			}

			break;
		case UP:
			m_collider.SetPosition(m_position.x, m_position.y - GetSize()); //Move the collider left
			if (m_collider.IsColliding(m->GetCollider()))
			{
				return false;
			}

			break;
		case DOWN:
			m_collider.SetPosition(m_position.x, m_position.y + GetSize()); //Move the collider left
			if (m_collider.IsColliding(m->GetCollider()))
			{
				return false;
			}

			break;
		}
	}

	//Check walls
	for (Cell* c : allCells)
	{
		switch (movement)
		{
		case LEFT:
			m_collider.SetPosition(m_position.x - GetSize(), m_position.y); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();
				if (numCell == 30)
				{
					m_onPlaceSnd.Play();
					m_OnPlace = true;
					m_state->CheckIfComplete();
				}
				else
				{
					m_OnPlace = false;
				}
				
				return c->IsWalkable();

			}
			break; 
		case RIGHT:
			m_collider.SetPosition(m_position.x + GetSize(), m_position.y); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();
				if (numCell == 30)
				{
					m_onPlaceSnd.Play();
					m_OnPlace = true;
					m_state->CheckIfComplete();
				}
				else
				{
					m_OnPlace = false;
				}
				return c->IsWalkable();

			}
			break;
		case UP:
			m_collider.SetPosition(m_position.x , m_position.y- GetSize()); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();
				if (numCell == 30)
				{
					m_onPlaceSnd.Play();
					m_OnPlace = true;
					m_state->CheckIfComplete();
				}
				else
				{
					m_OnPlace = false;
				}
				return c->IsWalkable();
			}
			break;
		case DOWN:
			m_collider.SetPosition(m_position.x , m_position.y+ GetSize()); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();
				if (numCell == 30)
				{
					m_onPlaceSnd.Play();
					m_OnPlace = true;
					m_state->CheckIfComplete();
				}
				else
				{
					m_OnPlace = false;
				}
				return c->IsWalkable();
			}
			break;
		}
	}
	return true;
}
