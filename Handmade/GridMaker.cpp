#include "GridMaker.h"
#include "Screen.h"
#include "Movable.h"
#include "Player.h"
#include "PlayState.h"

GridMaker::GridMaker(PlayState* state)
{
	m_state = state;
}

void GridMaker::CreateLevel(std::vector<Cell*>& allcells ,  int width, int height, const std::vector<std::string>& LevelData)
{
	allcells.clear();
	int c = 0;	//current tile
	int _width = Screen::Instance()->GetResolution().x;
	int _height = Screen::Instance()->GetResolution().y;
	int middleX = _width / 2 - (50 * width / 2);		//find the middle X position
	int middleY = _height / 2 - (50 * height / 2);		//find the middle Y position


	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Cell* newCell;
			//check the Number of the cell
			int cellNumber = std::stoi(LevelData[c + 2]); // +2 is because the first 2 numbers from data is (width and height)

			if (cellNumber == 32)
			{
				std::cout << "Create Movable";
				Movable* ball = new Movable(i * 50 + middleX, j * 50 + middleY, std::to_string(32));
				ball->SetPlayState(m_state);
				m_state->AddMovable(*ball);
			}

			else if (cellNumber == 28 || cellNumber == 29)		//If the tile is Player Put the player 28= Player 1 , 29= Player2
			{
				//Create Floor at the botton of the Player
				newCell = new Cell(i * 50 + middleX, j * 50 + middleY, std::to_string(22));
				newCell->SetTile(22);
				allcells.push_back(newCell);

				switch (cellNumber)
				{
				case 28:
					Player* p1;
					p1 = new Player(i * 50 + middleX, j * 50 + middleY, std::to_string(28));
					p1->IsControllable(true);	//Can control this Player
					p1->SetPlayState(m_state);		//Pass the PlayState to the Player
					m_state->SetPlayer(1, *p1);			//Put the Player in the vector
					break;
				case 29:
					Player * p2;
					p2 = new Player(i * 50 + middleX, j * 50 + middleY, std::to_string(29));
					p2->IsControllable(false);	//This Player is for Player2
					p2->SetPlayState(m_state);		//Pass the PlayState to the Player
					m_state->SetPlayer(2, *p2);		//Put the Player in the vector
					break;
				}
			}
			else if (cellNumber == -1)			//If the tile is Empty tile
			{
				newCell = new Cell(i * 50 + middleX, j * 50 + middleY, std::to_string(0));
				newCell->SetTile(0);
				allcells.push_back(newCell);
			}
			else	//If the tile is anything else Creat it also
			{
				newCell = new Cell(i * 50 + middleX, j * 50 + middleY, std::to_string(cellNumber));
				newCell->SetTile(cellNumber);
				allcells.push_back(newCell);
			}
			c++;
		}
	}
}
