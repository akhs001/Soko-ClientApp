#include <iostream>
#include "Debug.h"

//get handle on console output window
HANDLE Debug::s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

//------------------------------------------------------------------------------------------------------
//function that freezes console window until a key is pressed
//------------------------------------------------------------------------------------------------------
void Debug::PauseLog()
{

	system("pause");

}
//------------------------------------------------------------------------------------------------------
//function that clears the console window screen
//------------------------------------------------------------------------------------------------------
void Debug::ClearLog()
{

	system("cls");

}
//------------------------------------------------------------------------------------------------------
//function that displays simple numeric data
//------------------------------------------------------------------------------------------------------
void Debug::Log(float value, const std::string& label)
{

	//set color to a bright white
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));

	//display numeric data and if there is a label
	//to identify the data then display that first

	if (!label.empty())
	{
		std::cout << "[" << label << "] ";
	}

	std::cout << value << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that displays vector data using the above routine
//------------------------------------------------------------------------------------------------------
void Debug::Log(int x, int y, const std::string& label)
{

	Log({ x, y }, label);

}
//------------------------------------------------------------------------------------------------------
//function that displays vector data in separate coordinate format
//------------------------------------------------------------------------------------------------------
void Debug::Log(const SDL_Point& point, const std::string& label)
{

	//set color to a bright white
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));

	//display vector data in coordinate format and if there
	//is a label to identify the data then display that first

	if (!label.empty())
	{
		std::cout << "[" << label << "] ";
	}

	std::cout << "x = " << point.x << ", y = " << point.y << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that displays a message in a particular color
//------------------------------------------------------------------------------------------------------
void Debug::Log(const std::string& message, ErrorCode errorCode)
{

	//set color based on the numeric error code passed
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(errorCode));

	//display the message on the console
	std::cout << message << std::endl;
	
	//set color back to a bright white so that if the
	//text is output elsewhere it will be regular white
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));

}