#pragma once
#include "Text.h"
#include "Vector2.h"


class TextBox
{
public:
	TextBox(Vector2::vector2 pos, Vector2::vector2 size, std::string text);
	~TextBox();

public:
	void Draw();
	void SetText(std::string txt);
private:
	Vector2::vector2 m_pos;
	int m_size;
	Text m_text;

};

