#pragma once
#include "Sprite.h"
#include "Sound.h"
#include "Vector2.h"

class Dice
{
public:
	Dice();
	~Dice();
public:
	void SetNumber(short number);
	short GetNumber();
	void CreateRanbdom(int posX, int posY);
	void SetPos(int x, int y);
	void Draw();

private:
	std::string m_ID;
	short m_number;
	short m_min;
	short m_max;
	Sprite m_image;
	Sound m_sound;
	Vector2::vector2 m_pos;
};

