#include "Movable.h"

Movable::Movable(int x, int y, std::string ID)
{
    m_canMove = true;
    m_position.x = x;
    m_position.y = y;
    m_size = { 50,50 };

    m_image.SetImageDimension(1, 1, IMAGE_SIZE, IMAGE_SIZE);
    m_image.SetSpriteDimension(m_size.x, m_size.y);
    m_image.SetImage(ID);

    m_collider.SetDimension(m_size.x, m_size.y);
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
    m_image.Draw(m_position.x , m_position.y);
    return true;
}

void Movable::Move(Movement movement, int amount)
{
	switch (movement)
	{
	case RIGHT:
		m_position.x += amount;
		break;
	case LEFT:
		m_position.x -= amount;
		break;
	case UP:
		m_position.y -= amount;
		break;
	case DOWN:
		m_position.y += amount;
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
	std::vector<Cell*> allCells = m_state->GetAllTiles();

	for (Cell* c : allCells)
	{
		switch (movement)
		{
		case LEFT:
			m_collider.SetPosition(m_position.x - 50, m_position.y); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();

				if (numCell == 0)	//if its Empty cell you can move
				{
					return true;
				}
				if (numCell >= 22)	//You can move with those tiles
				{
					return true;
				}
				if (numCell > 0 && numCell < 22)	//These are wall tile so you cannot move
				{
					return false;
				}
			}
			break;
		case RIGHT:
			m_collider.SetPosition(m_position.x + 50, m_position.y); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();

				if (numCell == 0)	//if its Empty cell you can move
				{
					return true;
				}
				if (numCell >= 22)	//You can move with those tiles
				{
					return true;
				}
				if (numCell > 0 && numCell < 22)	//These are wall tile so you cannot move
				{
					return false;
				}
			}
			break;
		case UP:
			m_collider.SetPosition(m_position.x , m_position.y-50); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();

				if (numCell == 0)	//if its Empty cell you can move
				{
					return true;
				}
				if (numCell >= 22)	//You can move with those tiles
				{
					return true;
				}
				if (numCell > 0 && numCell < 22)	//These are wall tile so you cannot move
				{
					return false;
				}
			}
			break;
		case DOWN:
			m_collider.SetPosition(m_position.x , m_position.y+50); //Move the collider left
			if (m_collider.IsColliding(c->GetCollider()))
			{
				//Check if c is passable or not
				int numCell = c->GetTile();

				if (numCell == 0)	//if its Empty cell you can move
				{
					return true;
				}
				if (numCell >= 22)	//You can move with those tiles
				{
					return true;
				}
				if (numCell > 0 && numCell < 22)	//These are wall tile so you cannot move
				{
					return false;
				}
			}
			break;
		}
	}
	return true;
}
