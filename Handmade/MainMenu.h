#ifndef MAIN_MENU_H
#define MAIN_MENU_H

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
| 'MainMenu' source files last updated in July 2020   							                |
#==============================================================================================*/

#include <string>
#include <vector>
#include "GameObject.h"
#include "Text.h"

//make sure not to use any arbitrary width and height
//but rather one that corresponds to the current resolution
const int MENU_TEXT_CHAR_W = 25;
const int MENU_TEXT_CHAR_H = 53;

class MainMenu : public GameObject
{

public:

	MainMenu();
	virtual ~MainMenu();

public:

	int GetMenuOption() const;
	void SetMenuText(const std::string& text);

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	void Reset();

private:

	int m_menuOptionChoice;
	int m_menuOptionActive;
	std::vector<Text> m_menuText;

};

#endif