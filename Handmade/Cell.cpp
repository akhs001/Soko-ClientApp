#include "Cell.h"




Cell::Cell(int x, int y,  std::string ID)
{
	m_ID = ID;
	m_xpos = x;
	m_ypos = y;

	m_sizeX = 50;
	m_sizeY = 50;
	m_image.SetImageDimension(1, 1, 256, 256);
	m_image.SetSpriteDimension(m_sizeX, m_sizeY);

	m_image.SetImage(ID);

	m_collider.SetDimension(m_sizeX , m_sizeY);
	m_collider.SetPosition(m_xpos, m_ypos);
}

Cell::~Cell()
{
	m_image.Unload();
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

