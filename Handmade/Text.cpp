#include "Debug.h"
#include "Screen.h"
#include "Text.h"

std::map<std::string, TTF_Font*>* Text::s_fonts = new std::map<std::string, TTF_Font*>;

//------------------------------------------------------------------------------------------------------
//static function that initializes SDL font sub-system 
//if font sub-system initialization failed, display error message and return false
//------------------------------------------------------------------------------------------------------
bool Text::Initialize()
{

	Debug::Log("Initializing font sub-system...");

	if (TTF_Init() == -1)
	{
		Debug::Log("Font sub-system did not initialize properly.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	Debug::Log("Font sub-system successfully setup", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	return true;

}
//------------------------------------------------------------------------------------------------------
//static function that loads font data from a raw font file 
//first check if font data exists in map and if it does display warning message
//and halt loading because we don't want to replace the existing font data
//otherwise, load font data from file using SDL font load function 
//and if font loading failed, display error message, else add it to the map
//we load the font file using a 'fontSize' variable that is used to set the resolution in memory
//the higher the font size when loading the font file, the better the quality, but slower
//the font size is measured in DPI and translates to pixel height of each letter in the text
//------------------------------------------------------------------------------------------------------
bool Text::Load(const std::string& filename, const std::string& mapIndex, FontSize fontSize)
{

	Debug::Log("Opening and reading font file: '" + filename + "'");

	if (s_fonts->find(mapIndex) != s_fonts->end())
	{
		Debug::Log("Font data already loaded in memory.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	TTF_Font* font = TTF_OpenFont(filename.c_str(), static_cast<int>(fontSize));

	if (!font)
	{
		Debug::Log("File could not be loaded.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	(*s_fonts)[mapIndex] = font;

	Debug::Log("File opened and read successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	return true;

}
//------------------------------------------------------------------------------------------------------
//static function that unloads single or multiple font data from memory
//if the 'mapIndex' string is empty it means we need to remove all font data
//otherwise it means a specific ID has been passed which indicates 
//that specific font data should be removed. In that case, we first see
//if it is in the map before removing it
//------------------------------------------------------------------------------------------------------
void Text::Unload(const std::string& mapIndex)
{

	if (!mapIndex.empty())
	{

		Debug::Log("Unloading font data: '" + mapIndex + "'");
	
		auto it = s_fonts->find(mapIndex);

		if (it == s_fonts->end())
		{
			Debug::Log("Font data not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
			Debug::Log("===============================================================");
		}

		else
		{
			TTF_CloseFont(it->second);
			s_fonts->erase(it);

			Debug::Log("Font data unloaded successfully.", Debug::ErrorCode::SUCCESS);
			Debug::Log("===============================================================");
		}
	}

	else
	{

		Debug::Log("Unloading all font data.");

		for (auto it = s_fonts->begin(); it != s_fonts->end(); it++)
		{
			TTF_CloseFont(it->second);
		}

		s_fonts->clear();

		Debug::Log("All font data unloaded successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");

	}

}
//------------------------------------------------------------------------------------------------------
//static function that closes down SDL font sub-system
//------------------------------------------------------------------------------------------------------
void Text::ShutDown()
{

	TTF_Quit();

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Text::Text()
{

	m_font = nullptr;
	m_texture = nullptr;
	m_textSize = { 0, 0 };
	m_color = { 255, 255, 255 };

}
//------------------------------------------------------------------------------------------------------
//copy constructor that makes deep copies of object
//these are needed because when making copies of the 'Text' object the 'SDL_Texture' 
//pointer needs a deep copy made. This is not the case for 'TTF_Font', which is simply
//a reference to a single-existing resource, such as in the other component classes
//the texture is generated everytime we create a new font object, using the font resource
//'CreateText()' guarantees us that the texture is generated. This texture is deleted when object is destroyed
//TODO: consider using 'move semantics' to create a 'move constructor'
//------------------------------------------------------------------------------------------------------
Text::Text(const Text& copy)
{

	m_text = copy.m_text;
	m_font = copy.m_font;
	m_color = copy.m_color;
	m_textSize = copy.m_textSize;
	m_texture = nullptr;
	CreateText();

}
//------------------------------------------------------------------------------------------------------
//destructor that removes final SDL texture from memory
//we need this or there will always be one remaining texture object left over
//------------------------------------------------------------------------------------------------------
Text::~Text()
{

	SDL_DestroyTexture(m_texture);

}
//------------------------------------------------------------------------------------------------------
//getters and setters
//in 'SetText()' and 'SetColor()' we have to call 'CreateText()' so that a new texture
//is generated using the new text, new color and the font resource
//------------------------------------------------------------------------------------------------------
const SDL_Point& Text::GetSize() const
{

	return m_textSize;

}
//------------------------------------------------------------------------------------------------------
const std::string& Text::GetText() const
{
	
	return m_text;

}
//------------------------------------------------------------------------------------------------------
void Text::SetSize(int width, int height)
{

	m_textSize.x = width;
	m_textSize.y = height;

}
//------------------------------------------------------------------------------------------------------
void Text::SetText(const std::string& text)
{

	m_text = text;
	CreateText();

}
//------------------------------------------------------------------------------------------------------
void Text::SetColor(Uint8 r, Uint8 g, Uint8 b)
{

	m_color.r = r;
	m_color.g = g;
	m_color.b = b;

	CreateText();

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns font object based on index value passed
//first we must check if font data exists in map and if not display
//warning message, otherwise go ahead and assign the handle
//------------------------------------------------------------------------------------------------------
bool Text::SetFont(const std::string& mapIndex)
{

	auto it = s_fonts->find(mapIndex);

	if (it == s_fonts->end())
	{
		Debug::Log("Font data not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	m_font = (*it).second;
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that draws the actual text on screen
//------------------------------------------------------------------------------------------------------
void Text::Draw(int positionX, int positionY)
{

	SDL_Rect dst;

	//assign dimension of rectangular block to which text will be rendered to on screen
	dst.x = positionX;
	dst.y = positionY;
	dst.w = m_textSize.x;
	dst.h = m_textSize.y;

	//render the text object using all values passed and determined above
	SDL_RenderCopy(Screen::Instance()->GetRenderer(), m_texture, nullptr, &dst);

}
//------------------------------------------------------------------------------------------------------
//function that creates the actual text object
//------------------------------------------------------------------------------------------------------
void Text::CreateText()
{
	//create text object using font style, text string and color 
	//value and store in a temporary pointer to be used below
	SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);

	//free the old texture first before creating a new
	//texture object from surface object loaded above
	SDL_DestroyTexture(m_texture);
	m_texture = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), textSurface);

	//remove temporary SDL surface object as we don't need it anymore
	SDL_FreeSurface(textSurface);

}