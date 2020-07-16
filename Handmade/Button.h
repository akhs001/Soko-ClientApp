#pragma once
#include "GameObject.h"
#include "Text.h"
#include "Sprite.h"
#include "AABB.h"
#include "Sound.h"
#include "Vector2.h"

class MenuState;


class Button : public GameObject
{
public:
	//Button();
	Button(int  x, int y, Vector2 size, const std::string& text, const  std::string& ID);
	~Button();
public:
	virtual void Update(int deltaTime);
	virtual bool Draw();

	bool isClicked();
	bool CanClick();
	void SetColor(int color);
	void SetMenuState(MenuState* state);
	void CanClick(bool flag);
	int GetColor();
	//Vector2 GetPos();
	//MenuState* GetState();

	//Vector2 GetSize();
	void SetImage(std::string  ImageID);

private:
	int m_color;
	bool m_canClick;
	Sound m_click;
	std::string m_ID;
	Text m_text;
	Sprite m_image;
	Vector2 m_size;
	AABB m_collider;
	Vector2 m_pos;
	MenuState* m_state;
};

