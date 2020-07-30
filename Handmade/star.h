#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include <iostream>


class star
{
	public:
		star(Vector2::vector2 pos,  std::string filename);
		~star();

	public:
		void Draw();

	private:
		Vector2::vector2 m_pos;
		int m_size;
		Sprite m_image;

};

