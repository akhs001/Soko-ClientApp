#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "AABB.h"

const int SIZE_OF_TILES = 50;
const int IMAGE_SIZE = 128;

struct vector2
{
	int x;
	int y;
};

class PlayState;

class Player : public GameObject
{
public:
	Player(int x, int y,  std::string ID);
	~Player();

public:
	void Update(int deltaTime);
	bool Draw();
	void SetPlayState(PlayState* state) { m_state = state; };
	bool CheckCollision();
	bool IsControllable() { return m_canControl; }
	void IsControllable(bool flag) { m_canControl = flag;  }
	AABB GetCollider() { return m_collider;  }
private:
	bool m_canControl;
	Sprite m_image;
	vector2 m_position;
	vector2 m_size;
	bool m_canMove;
	AABB m_collider;
	PlayState* m_state;
};

