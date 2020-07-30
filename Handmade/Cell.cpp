#include "Cell.h"




Cell::Cell(int x, int y, int size , std::string ID)
{
	m_isWalkable = false;
	m_ID = ID;
	m_xpos = x;
	m_ypos = y;

	m_sizeX = size;
	m_sizeY = size;
	m_image.SetImageDimension(1, 1, 256, 256);
	m_image.SetSpriteDimension(size, size);

	m_image.SetImage(ID);

	m_collider.SetDimension(size, size);
	m_collider.SetPosition(m_xpos, m_ypos);
}

Cell::~Cell()
{
	m_image.Unload(m_ID);
}

void Cell::Update(int deltaTime)
{
	m_collider.SetPosition(m_xpos, m_ypos);
}

bool Cell::Draw()
{
	m_image.Draw(m_xpos , m_ypos);
	return true;
}

bool Cell::IsWalkable()
{
	switch (m_Tile)
	{
	case -1:return true;
	case 0:return true;
	case 1:return false;
	case 2:return false;
	case 3:return false;
	case 4:return false;
	case 5:return false;
	case 6:return false;
	case 7:return false;
	case 8:return false;
	case 9:return false;
	case 10:return false;
	case 11:return false;
	case 12:return false;
	case 13:return false;
	case 14:return  false;
	case 15:return false;
	case 16:return false;
	case 17:return false;
	case 18:return  false;
	case 19:return false;
	case 20:return false;
	case 21:return false;
	case 22:return true;
	case 23:return true;
	case 24:return true;
	case 25:return true;
	case 26:return true;
	case 27:return true;
	case 30:return true;
	case 31:return true;
	case 35:return false;
	case 37:return false;
	case 38:return false;
	case 39:return false;
	case 40:return false;
	case 41:return false;
	case 42:return false;
	case 43:return false;
	case 44:return false;
	}
}
