#ifndef TEXT_H
#define TEXT_H

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
| 'Text' source files last updated in July 2020   							                    |
#==============================================================================================*/

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{

public:

	enum class FontSize { SMALL = 72, MEDIUM = 144, LARGE = 300 };  //based on 72DPI - keep in multiples of 6

public:

	static bool Initialize();
	static bool Load(const std::string& filename, 
		             const std::string& mapIndex, FontSize fontSize = FontSize::SMALL);
	static void Unload(const std::string& mapIndex = "");
	static void ShutDown();

public:

	Text();
	Text(const Text& copy);
	~Text();

public:

	const SDL_Point& GetSize() const;
	const std::string& GetText() const;

public:

	void SetSize(int width, int height);
	void SetText(const std::string& text);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	bool SetFont(const std::string& mapIndex);

public:

	void Draw(int positionX = 0, int positionY = 0);

private:

	void CreateText();

private:

	static std::map<std::string, TTF_Font*>* s_fonts;

private:

	std::string m_text;               //the raw string text that is used to created the text object to be rendered
	SDL_Point m_textSize;             //size (in pixels) of the rendered text in its entirety

	TTF_Font* m_font;                 //handle on the font in memory. This is only a reference (no need for copy ctor)
	SDL_Color m_color;                //color of the rendered text
	SDL_Texture* m_texture;           //handle on the text object after using font, color and string to create it

};

#endif