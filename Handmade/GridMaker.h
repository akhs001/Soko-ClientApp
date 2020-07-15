#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cell.h"

class PlayState;

class GridMaker
{
public:
	GridMaker(PlayState* state);

public:
	void CreateLevel(std::vector<Cell*>& allcells,  int width, int height, const std::vector<std::string>& LevelData);

private :
	PlayState* m_state;
};

