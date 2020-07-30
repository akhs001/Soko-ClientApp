#pragma once
#include "GameObject.h"
#include "PlayState.h"
#include "Vector2.h"
#include "Sprite.h"
#include "Sound.h"


class Movable :public GameObject
{
public:
	Movable(int x, int y,int size, std::string ID);
	~Movable();

public:
	void Update(int deltaTime);
	bool Draw();
	void SetPlayState(PlayState* state) { m_state = state; };
	AABB GetCollider() { return m_collider;  }
	void Move(Movement movement, int amount);
	bool CanMove(Movement movement);
	int GetSize() { return m_size.x; }
	vector2 GetPos() { return  m_position; }
	void SetPos(vector2 pos) { m_position = pos; }
private:
	std::string m_ID;
	Sprite m_image;
	vector2 m_position;
	vector2 m_size;
	bool m_canMove;
	AABB m_collider;
	PlayState* m_state;
	Sound m_onPlaceSnd;
	Sound m_moveSnd;
	bool AlreadyAdd;
};

