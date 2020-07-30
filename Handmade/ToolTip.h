#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include <iostream>


class ToolTip
{
public:
	ToolTip( std::string filename);
	~ToolTip();

public :
	void Draw();

private :
	Vector2::vector2 m_pos;
	int m_size;
	Sprite m_image;
	Sprite m_BG;
};

