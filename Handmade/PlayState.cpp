
#include "Game.h"
#include "Input.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Utils.h"
#include "Sprite.h"
#include "Screen.h"
#include "Player.h"
#include "Movable.h"
#include "Button.h"
#include "Vector2.h"

static bool isStaffLoaded = false;

PlayState::PlayState(std::string file, bool Multiplayer, std::vector<LevelData> SavedData, int current)
{
	m_myDice = nullptr;
	m_Client = nullptr;
	connectionProblem = false;
	isGameStarted = false;
	currentLevel = current;
	m_levels = SavedData;
	m_Player1 = nullptr;
	m_Player2 = nullptr;
	m_level = "";
	btn_Back = nullptr;
	btn_Reset = nullptr;
	m_isMultiplayer = Multiplayer;
	strcpy_s( filename , file.c_str() );
}

bool PlayState::OnEnter()
{
	if (m_isMultiplayer)
	{
		m_Client = new TCPConnection;
		m_Client->SetState(this);
	}
	//Load All staff here
	if (!isStaffLoaded)
	{
		Sprite::Load("Assets/Images/start_1.png", "STAR");
		Sound::Load("Assets/Sounds/click.wav", "CLICK");
		Sound::Load("Assets/Sounds/wrongMove.wav", "WRONG");
		Sound::Load("Assets/Sounds/PlayerMove.wav", "P_MOVE");

		Sprite::Load("Assets/Images/BG/bg.png", "BACK");
		//load font resource into memory
		Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
		Text::Load("Assets/Fonts/Impact.ttf", "FONT", Text::FontSize::SMALL);

		//Load the dices
		for (size_t i = 1; i < 7; i++)
		{
			std::string name = "D" + std::to_string(i) + ".png";
			Sprite::Load("Assets/Dice/" + name, "D" + std::to_string(i));
		}

		for (int i = 0; i < 45; i++)
		{
			std::string name = std::to_string(i) + ".png";
			std::string filename = "Assets/mapImages/Decor_Tiles/" + name;
			Sprite::Load(filename, std::to_string(i));
		}

		isStaffLoaded = true;

	}

	Background.SetImageDimension(1, 1, 1921, 1080);
	Background.SetSpriteDimension(Screen::Instance()->GetResolution().x, Screen::Instance()->GetResolution().y);
	Background.SetImage("BACK");


	m_timeToStart = 30;
	TotalBalls = 0;
	BallsOnPlace = 0;
	IsGameRunning = true;


	isBackPressed = false;

	Background.SetImageDimension(1, 1, 1921, 1080);
	Background.SetSpriteDimension(Screen::Instance()->GetResolution().x, Screen::Instance()->GetResolution().y);
	Background.SetImage("BACK");

	//Create the button
	btn_Back = new Button(10, 10, Vector2::vector2({ 100, 50 }), "BACK", "BUTTON", false);
	btn_Back->SetMenuState(this);
	btn_Reset = new Button(10, 70, Vector2::vector2({ 100, 50 }), "RESET", "BUTTON", false);
	btn_Reset->SetMenuState(this);

	if (filename != nullptr && !m_isMultiplayer)
	{
		StartGame(filename , currentLevel);
	}
	else
	{
		std::cout << "MutiPlayer Game started" << std::endl;
		m_Client->Initialize(1255);
		if (m_Client->OpenSocket())
		{
			connectionProblem = false;
			t = new TextBox({ 10,300 }, { 200,100 }, "Get Ready");
			m_texts.push_back(t);
		}
		else
		{
			Utils::ShowMessage("Problem Connecting to the Server", "Connection Problem");
			connectionProblem = true;
		}

	}

	m_myDice = new Dice;
	m_myDice->CreateRanbdom(15, 300);
	return true;
}



float counter = 0.0f;
GameState* PlayState::Update(int deltaTime)
{
	if (connectionProblem)
	{
		return new MenuState;
	}


	if (!isGameStarted)
	{
		m_timeToStart -= 0.1f;

		if (m_timeToStart <= 0.0f)
		{
			isGameStarted = true;
			m_timeToStart = 30;
			m_texts.clear();
		}

	}


	//Check if the level is complete
	CheckIfComplete();

	std::string data ;
	//receive message

	if (isBackPressed)
	{
		isBackPressed = false;
		return new MenuState;
	}
	//Update Players
	for (Player* p : Players)
	{
		if (p != nullptr)
			p->Update(1);
	}

	for (Movable* m : Movables)
	{
		if (m != nullptr)
			m->Update(1);
	}

	for (Cell* c : m_Tiles)
	{
		if (c != nullptr)
			c->Update(1);
	}

	btn_Back->Update(1);
	btn_Reset->Update(1);

	if (isLevelComplete)
	{
		counter += 0.1f;

		if (counter > 5)
		{
			Utils::ShowMessage("Level Cleared", "Good Job");
			isLevelComplete = false;
			counter = 0.0f;
			//Save Progress
			if (!IsMultiPlayer())
			{
				m_levels[currentLevel - 1].isPassed = 1;
				SaveData(m_levels);
				std::cout << "Data saved" << std::endl;
			}
			return new MenuState;
		
		}
	}

	if (m_isMultiplayer)
	{
		m_Client->Receive(data);
	}


	//otherwise return reference to self
	//so that we stay in this game state
	return this;

}
//------------------------------------------------------------------------------------------------------
//function that renders all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Draw()
{
	Background.Draw();

	btn_Back->Draw();
	btn_Reset->Draw();

	for (Cell* c : m_Tiles)
	{
		if (c != nullptr)
			c->Draw();
	}


	for (Movable* m : Movables)
	{
		if (m != nullptr)
			m->Draw();
	}

	for (Player* p : Players)
	{
		if (p != nullptr)
			p->Draw();
	}
	
	for (TextBox* t : m_texts)
	{
		t->Draw();
	}

	//Draw my dice
	if (m_myDice != nullptr)
	{
		m_myDice->Draw();
	}


	return true;
}
//------------------------------------------------------------------------------------------------------
//function that removes all game objects from memory
//------------------------------------------------------------------------------------------------------
void PlayState::OnExit()
{
	IsGameRunning = false;
	delete m_Player1;
	delete m_Player2;
	delete btn_Back;
	delete btn_Reset;
	delete m_myDice;
	m_Tiles.clear();

		Sprite::Unload("STAR");
		Sound::Unload("CLICK");
		Sound::Unload("WRONG");
		Sound::Unload("P_MOVE");

		Sprite::Unload("BACK");
		Text::Unload("Menu_Font");
		Text::Unload("FONT");
		isStaffLoaded = false;

}

std::vector<Cell*> PlayState::GetAllTiles()
{
	return m_Tiles;
}

std::vector<Movable*> PlayState::GetAllMovables()
{
	return Movables;
}

std::vector<Player*> PlayState::GetAllPlayers()
{
	return Players;
}

bool PlayState::IsMultiPlayer()
{
	return m_isMultiplayer;
}

bool PlayState::IsGaneStarted()
{
	return isGameStarted;
}

bool PlayState::OpenFile()
{
		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = ("Level Files\0*.bin\0");
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = ("Select a Level To Play!");
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn))
		{
			std::cout << "File Opened \"" << filename << "\"\n";
			return true;
		}
		else
		{
			std::cout << "Error Opening the file \"" << filename << "\"\n";
			return false;
		}

}



std::string PlayState::GetFilename()
{
	return  filename;
}

void PlayState::StartGame( std::string fileName , int level)
{
	Movables.clear();
	Players.clear();
	m_Tiles.clear();
	TotalBalls = 0;
	BallsOnPlace = 0;
	currentLevel = level;

	std::ifstream file(fileName, std::ios_base::binary);

	//get the size
	int width = 0;
	int height = 0;
	file.read((char*)(&width), sizeof(int));
	file.read((char*)(&height), sizeof(int));


	if (width < 5 || height < 5 || width > MAX_WIDTH || height > MAX_HEIGHT)
	{
		Utils::ShowMessage("An error found when loading the level.Maybe the leves is corrupted", "Error level");
		return;
	}



	int NumCells = width * height;

	int _width = Screen::Instance()->GetResolution().x;
	int _height = Screen::Instance()->GetResolution().y;
	//Calculate the tile size
	 tileS = (_height - 100) / width;

	float middleX = _width * 0.5f - (tileS * width * 0.5f);
	float middleY = _height * 0.5f - (tileS * height * 0.5f);

	Cell* thecell;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//check the Number of the cell
			int cellNumber;
			file.read((char*)&cellNumber, sizeof(int));


			if (cellNumber == 32)
			{
				Movable* ball = new Movable(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(32));
				ball->SetPlayState(this);
				Movables.push_back(ball);
				TotalBalls++;
			}
			else if (cellNumber == 28 || cellNumber == 29)		//If the tile is Player Put the player 28= Player 1 , 29= Player2
			{

				switch (cellNumber)
				{
				case 28:
					Player * p1;
					p1 = new Player(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(28));
					p1->IsControllable(true);	//Can control this Player
					p1->SetPlayState(this);		//Pass the PlayState to the Player
					SetPlayer(1, *p1);			//Put the Player in the vector
					break;
				case 29:
					Player * p2;
					p2 = new Player(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(29));
					p2->IsControllable(false);	//This Player is for Player2
					p2->SetPlayState(this);		//Pass the PlayState to the Player
					SetPlayer(1, *p2);			//Put the Player in the vector
					break;
				}
			}
			else
			{
				
				std::string name = std::to_string(cellNumber) + ".png";
				std::string id = "TILE_" + std::to_string(cellNumber);
				std::string filename = "Assets/mapImages/Decor_Tiles/" + name;
				thecell = new Cell(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(cellNumber));
				thecell->SetTile(cellNumber);
				thecell->SetWalkable(thecell->IsWalkable());		//Set if the cell is walkable or not
				m_Tiles.push_back(thecell);
			}
		}
	}
	file.close();
}

void PlayState::StartGameS(std::string data)
{
	Movables.clear();
	Players.clear();
	m_Tiles.clear();
	TotalBalls = 0;
	BallsOnPlace = 0;

	//Get the Data and store them to a vector
	std::vector<std::string> levelData = Utils::Split(data, ',');

	//get the size
	int width = std::stoi( levelData[0]);
	int height = std::stoi(levelData[1]);

	levelData.erase(levelData.begin());
	levelData.erase(levelData.begin());


	int NumCells = width * height;

	int _width = Screen::Instance()->GetResolution().x;
	int _height = Screen::Instance()->GetResolution().y;
	//Calculate the tile size
	int tileS = (_height - 100) / width;

	float middleX = _width * 0.5f - (tileS * width * 0.5f);
	float middleY = _height * 0.5f - (tileS * height * 0.5f);

	int currentTile = 0;
	Cell* thecell;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//check the Number of the cell
			int cellNumber = std::stoi(levelData[currentTile]);



			if (cellNumber == 32)
			{
				Movable* ball = new Movable(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(32));
				ball->SetPlayState(this);
				Movables.push_back(ball);
				BallsOnPlace++;
			}
			else if (cellNumber == 28 || cellNumber == 29)		//If the tile is Player Put the player 28= Player 1 , 29= Player2
			{
				switch (cellNumber)
				{
				case 28:
					Player * p1;
					p1 = new Player(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(28));
					p1->IsControllable(false);	//Can control this Player
					p1->SetPlayState(this);		//Pass the PlayState to the Player
					SetPlayer(1, *p1);			//Put the Player in the vector
					break;
				case 29:
					Player * p2;
					p2 = new Player(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(29));
					p2->IsControllable(true);	//This Player is for Player2
					p2->SetPlayState(this);		//Pass the PlayState to the Player
					SetPlayer(1, *p2);			//Put the Player in the vector
					break;
				}
			}
			else
			{

				std::string name = std::to_string(cellNumber) + ".png";
				std::string id = "TILE_" + std::to_string(cellNumber);
				std::string filename = "Assets/mapImages/Decor_Tiles/" + name;
				thecell = new Cell(i * tileS + middleX, j * tileS + middleY, tileS, std::to_string(cellNumber));
				thecell->SetTile(cellNumber);
				thecell->SetWalkable(thecell->IsWalkable());		//Set if the cell is walkable or not
				m_Tiles.push_back(thecell);
			}

			currentTile++;
		}
	}
}

void PlayState::GoBack()
{
	isBackPressed = true;
}

int PlayState::GetTileSize()
{
	return tileS;
}

void PlayState::AddBallInPlace()
{
	BallsOnPlace++;
	std::cout << BallsOnPlace << "/" << TotalBalls << std::endl;
}

void PlayState::MoveBallOutOfPlace()
{
	BallsOnPlace--;
	std::cout << BallsOnPlace << "/" << TotalBalls << std::endl;
}

int PlayState::GetBallsOnPlace()
{
	return BallsOnPlace;
}

int PlayState::GetTotalBalls()
{
	return TotalBalls;
}


void PlayState::SaveData(std::vector<LevelData>& data)
{
	std::ofstream file("Save.dat",  std::ios_base::binary);

	for (int i = 0; i < data.size(); i++)
	{
		file.write((char*)&data[i].level, sizeof(int));
		file.write((char*)&data[i].isPassed, sizeof(int));
	}


	file.close();
	std::cout << "Data saved" << std::endl;
}

int PlayState::GetCurrentLevel()
{
	return currentLevel;
}



void PlayState::UpdateMovables()
{
	if (!IsMultiPlayer()) { return; }
	std::string positions = "P";

	for (Movable* m : Movables)
	{
		positions += std::to_string(m->GetPos().x) + ":" + std::to_string(m->GetPos().y) + ",";
	}

	m_Client->Send(positions);
}

void PlayState::UpdateMovables(std::string Data)
{
	//Get All the Positions
	if (!IsMultiPlayer()) { return; }
	std::vector < std::string > Positions = Utils::Split(Data, ',');

	int c = 0;
	for (Movable* m : Movables)
	{
		//Get the pos
	
	std::vector <std::string> pos = Utils::Split( Positions[c], ':');

	m->SetPos({std::stoi( pos[0]) ,std::stoi( pos[1]) });
	c++;
	}
}

void PlayState::UpdatePlayer()
{
	if (!IsMultiPlayer()) { return; }
	std::string positions = "M";

	for (Player* p : Players)
	{
		positions += std::to_string(p->GetPos().x) + ":" + std::to_string(p->GetPos().y) + ",";
	}

	m_Client->Send(positions);
}

//Get Update message from server
void PlayState::UpdateServerPosition(std::string Data)
{
	if (!IsMultiPlayer()) { return; }
	std::vector < std::string > Positions = Utils::Split(Data, ',');

	int c = 0;
	for (Player* p : Players)
	{
		std::vector <std::string> pos = Utils::Split(Positions[c], ':');

		p->SetPos({ std::stoi(pos[0]) ,std::stoi(pos[1]) });
		p->GetCollider().SetPosition(std::stoi(pos[0]), std::stoi(pos[1]));
		c++;
	}
}


void PlayState::AddMovable(Movable& moveable)
{
	Movables.push_back(&moveable);
}

void PlayState::SetPlayer(int player,  Player& playerObject)
{
	switch (player)
	{
	case 1:
		m_Player1 = &playerObject;
		Players.push_back(m_Player1);
		break;
	case 2:
		m_Player2 = &playerObject;
		Players.push_back(m_Player2);
		break;
	}
}

void PlayState::SetFileName(std::string fileName)
{
	strcpy_s(filename, fileName.c_str());
}

void PlayState::CheckIfComplete()
{
	if (!isGameStarted) { return;  }
	if (BallsOnPlace == TotalBalls)
	{
		//Level complete
		isLevelComplete = true;
	}
	else
	{
		isLevelComplete = false;
	}

}




