#ifndef GAME_STATE_H
#define GAME_STATE_H


struct LevelData
{
	int level;
	int isPassed;
};

class GameState
{

public:
	
	GameState() {}
	virtual ~GameState() = 0 {}

public:

	virtual bool OnEnter() = 0;
	virtual GameState* Update(int deltaTime) = 0;
	virtual bool Draw() = 0;
	virtual void OnExit() = 0;

	virtual std::string GetFilename() { return ""; }
	virtual void ShowLevels() {};
	virtual void StartGame() {};
	virtual void StartGame(std::string level , int lev) {};
	virtual void GoBack() {};
	virtual void Quit() {};
	virtual void IsMultiPlayer(bool flag) {  }
	virtual bool IsMultiPlayer() { return false; }
	virtual int GetCurrentLevel() { return 0; }
};

#endif