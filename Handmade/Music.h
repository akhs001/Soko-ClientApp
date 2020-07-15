#ifndef MUSIC_H
#define MUSIC_H

/*==============================================================================================#
|                                                                                               |
| Handmade Lite is an educational game engine, written by Karsten Vermeulen for the purposes of |
| educating other fellow programmers, programming students and anyone else wishing to learn     |
| about game development, C++ and OOP. The engine, class design and overall structure is by no  |
| means perfect and there is certainly room for improvement. Feel free to use, copy, break,     |
| update and do as you wish with this code - it is there, free, for all!                        |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|	                                                                                            |
| Please note, that this project is not open source and therefore has no license affiliated     |
| with it. However, feel free to use the engine to build your own game or learn from the code.  |
| Handmade Lite is an educational tool, designed to be used as such. Please be respectful and   |
| do not distribute the engine or its code as your own work. You may alter or tweak the engine  |
| code as a learning experience and you may also 'borrow' some code and functionality and use   |
| it to create your own game engine or game.                                                    |
|	                                                                                            |
#===============================================================================================#
|                                                                                               |
| If you like Handmade Lite and wish to show your support, if you have any questions about      |
| the project, or if you just want to reach out, please do get in touch:                        |
|																						        |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Music' source files last updated in June 2020   							                    |
#==============================================================================================*/

#include <map>
#include <string>
#include <SDL_mixer.h>

class Music
{

public:

	enum class LoopType  { PLAY_ONCE = 1, PLAY_ENDLESS = -1 };

public:

	static void Output();
	static bool Initialize(int frequency = 44100, int chunkSize = 1024);
	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");
	static void ShutDown();

public:

	Music();

public:

	void SetVolume(int volume);
	bool SetMusic(const std::string& mapIndex);

public:

	bool Play(LoopType loopType = LoopType::PLAY_ONCE);
	void Pause();
	void Resume();
	void Stop();    			

private:

	static std::map<std::string, Mix_Music*>* s_music;

private:
	
	Mix_Music* m_music;
					
};

#endif