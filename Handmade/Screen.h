#ifndef SCREEN_H
#define SCREEN_H

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
| 'Screen' source files last updated in May 2020   							                    |
#==============================================================================================*/

#include <string>
#include <SDL.h>
#include <SDL_syswm.h>

class Screen
{

public:

	static Screen* Instance();

public:

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Point GetResolution();

public:

	void SetMousePosition(int x, int y);
	void SetClearColor(Uint8 r, Uint8 g, Uint8 b);

public:

	bool Initialize(const std::string& windowTitle, int width = 1024, 
		            int height = 768, bool fullscreen = false);
	
	void Update();
	void Draw();

	void ShutDown();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

private:

	int m_width;
	int m_height;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	
};

#endif