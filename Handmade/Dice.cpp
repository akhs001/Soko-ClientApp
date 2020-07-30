#include "Dice.h"
#include <iostream>

static bool isLoaded = false;

Dice::Dice()
{
    m_min = 1;
    m_max = 6;
    m_pos = { 0,0 };
    m_number = 0;
    if (!isLoaded)
    {
        Sound::Load("Assets/Sounds/dice.wav", "DICESND");
        isLoaded = true;
    }
    m_sound.SetSound("DICESND");
}

Dice::~Dice()
{
    isLoaded = false;
    Sound::Unload("DICESND");
}

void Dice::SetNumber(short number)
{
    m_number = number;

    m_ID = "D" + std::to_string(m_number);
    m_image.SetImageDimension(1, 1, 256, 256);
    m_image.SetSpriteDimension(100, 100);
    m_image.SetImage(m_ID);
    m_sound.Play();
}

short Dice::GetNumber()
{
    return m_number;
}

void Dice::CreateRanbdom(int posX, int posY)
{
    short randomDice = (rand() % m_max) + 1;
 
    m_ID = "D" + std::to_string(randomDice);
    m_image.SetImageDimension(1, 1, 256, 256);
    m_image.SetSpriteDimension(100, 100);
    m_image.SetImage(m_ID);

    m_pos = { posX , posY };
    m_sound.Play();
}

void Dice::SetPos(int x, int y)
{
    m_pos = { x,y };
}

void Dice::Draw()
{
    m_image.Draw(m_pos.x , m_pos.y);
}
