#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);

public:
	void SetX(int xVal) { m_x = xVal; }
	int GetX() { return m_x; }
	void SetY(int yVal) { m_y = yVal; }
	int GetY() { return m_y; }

private :
	int m_x;
	int m_y;
};

