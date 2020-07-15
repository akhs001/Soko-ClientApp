#pragma once
#include "GameObject.h"
#include "PlayState.h"
//#include "AABB.h"
#include "Sprite.h"

class Movable :public GameObject
{
public:
	Movable(int x, int y, std::string ID);
	~Movable();

public:
	void Update(int deltaTime);
	bool Draw();
	void SetPlayState(PlayState* state) { m_state = state; };
	AABB GetCollider() { return m_collider;  }
	void Move(Movement movement, int amount);
	bool CanMove(Movement movement);
private:
	Sprite m_image;
	vector2 m_position;
	vector2 m_size;
	bool m_canMove;
	AABB m_collider;
	PlayState* m_state;

};
