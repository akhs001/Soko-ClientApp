#include "TextBox.h"

TextBox::TextBox(Vector2::vector2 pos, Vector2::vector2 size, std::string text)
{
	m_size = 20;
	m_pos = pos;

	m_text.SetFont("FONT");
	m_text.SetColor(0, 0, 0);

	m_text.SetSize(size.x, size.y);
	m_text.SetText(text);

}

TextBox::~TextBox()
{
	m_text.Unload();
}

void TextBox::Draw()
{
	m_text.Draw(m_pos.x, m_pos.y);
}

void TextBox::SetText(std::string txt)
{
	m_text.SetText( txt);
}
