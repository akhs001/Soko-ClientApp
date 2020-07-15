#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "AABB.h"

enum  Movement { RIGHT , LEFT , UP , DOWN};

class Cell :public GameObject
{
public:
	Cell(int x , int y ,std::string ID);
	~Cell();

public:
	void Update(int deltaTime) ;
	bool Draw();
	std::string GetID() { return m_ID;  }
	AABB GetCollider() { return m_collider;  }
	int GetTile() { return m_Tile;  }
	void SetTile(int tile) { m_Tile = tile; }


private:
	Sprite m_image;
	int m_xpos;
	int m_ypos;
	int m_sizeX;
	int m_sizeY;
	std::string m_ID;
	int m_Tile;
	AABB m_collider;
};

