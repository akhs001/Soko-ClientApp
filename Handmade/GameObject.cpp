#include "GameObject.h"

//------------------------------------------------------------------------------------------------------
GameObject::GameObject()
{

	m_angle = 0.0f;
	m_priority = 0;
	
	m_isAlive = true;
	m_isActive = true;
	m_isVisible = true;
	
}
//------------------------------------------------------------------------------------------------------
bool GameObject::IsAlive() const
{

	return m_isAlive;

}
//------------------------------------------------------------------------------------------------------
bool GameObject::IsActive() const
{

	return m_isActive;

}
//------------------------------------------------------------------------------------------------------
bool GameObject::IsVisible() const
{

	return m_isVisible;

}
//------------------------------------------------------------------------------------------------------
void GameObject::IsAlive(bool flag)
{

	m_isAlive = flag;

}
//------------------------------------------------------------------------------------------------------
void GameObject::IsActive(bool flag)
{

	m_isActive = flag;

}
//------------------------------------------------------------------------------------------------------
void GameObject::IsVisible(bool flag)
{

	m_isVisible = flag;

}
//------------------------------------------------------------------------------------------------------
float GameObject::GetAngle() const
{

	return m_angle;

}
//------------------------------------------------------------------------------------------------------
int GameObject::GetPriority() const
{

	return m_priority;

}
//------------------------------------------------------------------------------------------------------
const std::string& GameObject::GetTag() const
{

	return m_tag;

}
//------------------------------------------------------------------------------------------------------
const Vector<int>& GameObject::GetPosition() const
{

	return m_position;

}
//------------------------------------------------------------------------------------------------------
const Vector<int>& GameObject::GetDimension() const
{

	return m_dimension;

}
//------------------------------------------------------------------------------------------------------
void GameObject::SetPosition(int x, int y)
{

	m_position.x = x;
	m_position.y = y;

}
//------------------------------------------------------------------------------------------------------
void GameObject::SetDimension(int x, int y)
{

	m_dimension.x = x;
	m_dimension.y = y;

}
//------------------------------------------------------------------------------------------------------
void GameObject::SetTag(const std::string& tag)
{

	m_tag = tag;

}