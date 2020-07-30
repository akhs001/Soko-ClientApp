#include "star.h"
#include "Screen.h"

static bool isLoaded = false;
star::star(Vector2::vector2 pos,  std::string filename)
{
	m_size = 20;
	m_pos = pos;
	if (!isLoaded)
	{
		Sprite::Load(filename, "STAR");
		isLoaded = true;
	}

	m_image.SetImageDimension(1, 1, 82, 82);
	m_image.SetSpriteDimension(m_size, m_size);
	m_image.SetImage("STAR");

}

star::~star()
{
	isLoaded = false;
	m_image.Unload("STAR");
}

void star::Draw()
{
	m_image.Draw(m_pos.x , m_pos.y );
}
