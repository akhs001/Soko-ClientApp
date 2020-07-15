#include "AABB.h"

//------------------------------------------------------------------------------------------------------
//setter function that assigns position of AABB and creates the collision box
//------------------------------------------------------------------------------------------------------
void AABB::SetPosition(int x, int y)
{

	m_position.x = x;
	m_position.y = y;

	CreateBox();

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of AABB and creates the collision box
//------------------------------------------------------------------------------------------------------
void AABB::SetDimension(int width, int height)
{

	m_dimension.x = width; 
	m_dimension.y = height;

	CreateBox();

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with another AABB object
//------------------------------------------------------------------------------------------------------
bool AABB::IsColliding(const AABB& secondBox) const
{

	return ((m_max.x > secondBox.m_min.x && secondBox.m_max.x > m_min.x) &&
		    (m_max.y > secondBox.m_min.y && secondBox.m_max.y > m_min.y));

}
//------------------------------------------------------------------------------------------------------
//function that calculates min and max values of AABB for collision purposes
//------------------------------------------------------------------------------------------------------
void AABB::CreateBox()
{
	m_min.x = m_position.x;
	m_min.y = m_position.y;
	m_max.x = m_position.x + m_dimension.x;
	m_max.y = m_position.y + m_dimension.y;
	
}