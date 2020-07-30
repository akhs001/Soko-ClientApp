#include "ToolTip.h"
#include "Screen.h"



ToolTip::ToolTip( std::string filename)
{
	m_size = 350;
	m_pos.x = Screen::Instance()->GetResolution().x - m_size ;
	m_pos.y = Screen::Instance()->GetResolution().y * 0.5f - (m_size / 2);
	Sprite::Unload("TOOLTIP");
	Sprite::Load(filename, "TOOLTIP");
	Sprite::Load("Assets/level_select/table2.png", "BG");
	m_image.SetImageDimension(1, 1, 512, 512);
	m_image.SetSpriteDimension(300, 300);
	m_image.SetImage("TOOLTIP");

	m_BG.SetImageDimension(1, 1, 1002, 1100);
	m_BG.SetSpriteDimension(m_size, m_size);
	m_BG.SetImage("BG");
}

ToolTip::~ToolTip()
{
	m_BG.Unload("BG");
	m_image.Unload("TOOLTIP");
}

void ToolTip::Draw()
{
	m_BG.Draw(m_pos.x, m_pos.y);
	m_image.Draw(m_pos.x +25, m_pos.y +25);
}
