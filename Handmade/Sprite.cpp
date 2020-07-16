#include <algorithm>
#include <SDL_image.h>
#include "Debug.h"
#include "Sprite.h"
#include "Screen.h"

std::map<std::string, SDL_Texture*>* Sprite::s_images = new std::map<std::string, SDL_Texture*>;

//------------------------------------------------------------------------------------------------------
//static function that loads image data from a raw texture/image file 
//first check if image data exists in map and if it does display warning message
//and halt loading because we don't want to replace the existing image data
//otherwise, load music data from file using SDL image load function 
//and if image loading failed, display error message, else add it to the map
//before adding the image to the map, we first create a texture object out of the 
//previously loaded image and free the SDL image as its no longer needed
//------------------------------------------------------------------------------------------------------
bool Sprite::Load(const std::string& filename, const std::string& mapIndex)
{

	if (s_images->find(mapIndex) != s_images->end())
	{
		return false;
	}

	SDL_Surface* imageData = IMG_Load(filename.c_str());

	if (!imageData)
	{
		return false;
	}

	SDL_Texture* image = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), imageData);
	SDL_FreeSurface(imageData);

	(*s_images)[mapIndex] = image;
	return true;

}
//------------------------------------------------------------------------------------------------------
//static function that unloads single or multiple image data from memory
//if the 'mapIndex' string is empty it means we need to remove all image data
//otherwise it means a specific ID has been passed which indicates 
//that specific image data should be removed. In that case, we first see
//if it is in the map before removing it
//------------------------------------------------------------------------------------------------------
void Sprite::Unload(const std::string& mapIndex)
{

	if (!mapIndex.empty())
	{

		Debug::Log("Unloading image data: '" + mapIndex + "'");

		auto it = s_images->find(mapIndex);

		if (it == s_images->end())
		{

		}

		else
		{
			SDL_DestroyTexture(it->second);
			s_images->erase(it);

			Debug::Log("Image data unloaded successfully.", Debug::ErrorCode::SUCCESS);
			Debug::Log("===============================================================");
		}
	}

	else
	{

		Debug::Log("Unloading all image data.");

		for (auto it = s_images->begin(); it != s_images->end(); it++)
		{
			SDL_DestroyTexture(it->second);
		}

		s_images->clear();

		Debug::Log("All image data unloaded successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");

	}

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sprite::Sprite()
{

	m_imageIndex = 0;
	m_animationVelocity = 0.0f;
	
	m_isAnimated = false;
	m_isAnimationDead = false;
	m_isAnimationLooping = true;
	m_isAnimationLoopFinal = false;
	
	m_image = nullptr;
	m_celDimension = { 0, 0 };
	m_imageDimension = { 0, 0 };
	m_spriteDimension = { 0, 0 };

}
//------------------------------------------------------------------------------------------------------
//getters and setters
//------------------------------------------------------------------------------------------------------
bool Sprite::IsAnimationDead()
{

	return m_isAnimationDead;

}
//------------------------------------------------------------------------------------------------------
void Sprite::IsAnimated(bool flag)
{

	m_isAnimated = flag;

}
//------------------------------------------------------------------------------------------------------
bool Sprite::IsAnimationLooping()
{

	return m_isAnimationLooping;

}
//------------------------------------------------------------------------------------------------------
void Sprite::IsAnimationLooping(bool flag)
{

	m_isAnimationLooping = flag;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific position of image cel in image to 'cut out'
//here we use a specific algorithm to 'cut out' the image from the sprite sheet
//this is aimed for the static sprites that do not animate, where we want a specific image
//we also make sure no negative or zero values are passed as these are invalid
//when calculating the index value, we negate 1 because when rendering, positions are zero-based
//------------------------------------------------------------------------------------------------------
void Sprite::SetImageCel(int column, int row)
{

	row = std::max(row, 1);
	column = std::max(column, 1);

	m_imageIndex = ((row - 1) * m_imageDimension.x) + (column - 1);

}
//------------------------------------------------------------------------------------------------------
void Sprite::SetAnimationVelocity(float velocity)
{

	m_animationVelocity = velocity;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns image object based on index value passed
//first we must check if image data exists in map and if not display
//warning message, otherwise go ahead and assign the handle
//------------------------------------------------------------------------------------------------------
bool Sprite::SetImage(const std::string& mapIndex)
{

	auto it = s_images->find(mapIndex);

	if (it == s_images->end())
	{
		return false;
	}

	m_image = (*it).second;

	return true;

}
//------------------------------------------------------------------------------------------------------
void Sprite::SetSpriteDimension(int width, int height)
{

	m_spriteDimension.x = width;
	m_spriteDimension.y = height;

}
//------------------------------------------------------------------------------------------------------
//this is the dimension of the image on the hard drive
//the columns and rows are the grid-like dimensions of the image
//a sprite sheet might consist of 6 rows and 5 columns - a single image will be 1x1
//the width and height is the resolution of the image
//the function will use this data to calculate the dimension for each cel
//we use 'std::max' to make sure that no negative or zero dimensions are used
//------------------------------------------------------------------------------------------------------
void Sprite::SetImageDimension(int columns, int rows, int width, int height)
{

	rows = std::max(rows, 1);
	columns = std::max(columns, 1);

	m_imageDimension.x = columns;
	m_imageDimension.y = rows;

	m_celDimension.x = width / columns;
	m_celDimension.y = height / rows;

}
//------------------------------------------------------------------------------------------------------
//function that calculates what image in the spritesheet to cut out and display next
//here we use a formula and delta time to calcute with image cel is up next
//we also determine if the first cel needs to be displayed once the animation cycle is done
//if not, it stops looping
//------------------------------------------------------------------------------------------------------
void Sprite::Update(int deltaTime)
{

	//if sprite is an animation we have to calculate the 
	//image cel each frame because it won't be a static value
	if (m_isAnimated)
	{

		//we need to keep accumulating time for the formula below
		//this is done by adding on the delta time each frame
		//we divide by 1000.0f because its MS time and we need
		//to make sure that we don't trim the decimal portion 
		static float totalTime = 0.0f;
		totalTime += deltaTime / 1000.0f;

		//aquire index value of specific texture cel to 'cut out' using a formula
		//the image index is zero based and is a whole number value counting from
		//top left and going right and down the sprite sheet, and is capable of 'wrapping'
		m_imageIndex = static_cast<int>(totalTime * m_animationVelocity) %
			           static_cast<int>(m_imageDimension.x * m_imageDimension.y);
		
		//if animation is set to cycle endlessly then set the kill and final flags
		//to false so that no other final checks are made and that the animation loops
		if (m_isAnimationLooping)
		{
			m_isAnimationDead = false;
			m_isAnimationLoopFinal = false;
		}

		//otherwise if animation is set to cycle once and the last image
		//cel has been reached then flag this as the final animation loop
		else if (!m_isAnimationLooping &&
			     m_imageIndex == (m_imageDimension.x * m_imageDimension.y - 1))
		{
			m_isAnimationLoopFinal = true;
		}

		//if this is the final animation, flag to kill entire animation
		//because even though the animation is marked final, a few more 
		//frames will be called with the last image cel set, so only
		//mark it dead when the first image cel comes around again
		if (m_isAnimationLoopFinal && m_imageIndex == 0)
		{
			m_isAnimationDead = true;
		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that calculates the source and destination sections of the sprite and screen and renders
//only if animation is set to continue will the block of code execute (for animated types)
//for static sprite types, the animation is permanently set to run
//------------------------------------------------------------------------------------------------------
void Sprite::Draw(int positionX, int positionY, double angle, FlipType flipType)
{

	//if animation is set to run, then render the
	//sprite using the internal blitting function
	if (!m_isAnimationDead)
	{

		//variables to store rectangular dimensions for the source 
		//sprite and destination portion of the screen to render to 
		SDL_Rect src;
		SDL_Rect dst;

		//use modulo and divide with the image index to get exact cel block xy coordinates
		//to 'cut out' and assign all of this as well as width and height to the source rect
		src.x = (m_imageIndex % m_imageDimension.x) * m_celDimension.x;
		src.y = (m_imageIndex / m_imageDimension.x) * m_celDimension.y;
		src.w = m_celDimension.x;
		src.h = m_celDimension.y;

		//assign dimension of rectangular block to which sprite will be rendered to on screen
		dst.x = positionX;
		dst.y = positionY;
		dst.w = m_spriteDimension.x;
		dst.h = m_spriteDimension.y;

		//if sprite needs to be rotated, use the centre of the sprite as its centre of rotation
		SDL_Point centrePoint;
		centrePoint.x = m_spriteDimension.x / 2;
		centrePoint.y = m_spriteDimension.y / 2;

		//render the sprite using all values passed and determined above
		SDL_RenderCopyEx(Screen::Instance()->GetRenderer(),
			             m_image, &src, &dst, angle, &centrePoint, static_cast<SDL_RendererFlip>(flipType));

	}

}