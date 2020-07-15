#ifndef SPRITE_H
#define SPRITE_H

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
| 'Sprite' source files last updated in June 2020   						                    |
#==============================================================================================*/

#include <map>
#include <string>
#include <SDL_render.h>

class Sprite
{

public:

	enum class FlipType { NO_FLIP = SDL_FLIP_NONE, 
		                  HORIZONTAL = SDL_FLIP_HORIZONTAL, 
		                  VERTICAL = SDL_FLIP_VERTICAL };

public:

	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");

public:

	Sprite();           

public:

	bool IsAnimationDead();
	void IsAnimated(bool flag);
	bool IsAnimationLooping();
	void IsAnimationLooping(bool flag);

public:

	void SetImageCel(int column, int row);
	void SetAnimationVelocity(float velocity);
	bool SetImage(const std::string& mapIndex);
	void SetSpriteDimension(int width, int height);
	void SetImageDimension(int columns, int rows, int width, int height);
	
public:

	void Update(int deltaTime);
	void Draw(int positionX = 0, int positionY = 0, double angle = 0.0, 
		      FlipType flipType = FlipType::NO_FLIP);

private:

	static std::map<std::string, SDL_Texture*>* s_images;

private:

	int m_imageIndex;
	float m_animationVelocity;
	
	bool m_isAnimated;
	bool m_isAnimationDead;
	bool m_isAnimationLooping;
	bool m_isAnimationLoopFinal;

	SDL_Texture* m_image;               //handle on the image in memory. This is only a reference (no need for copy ctor)
	SDL_Point m_celDimension;           //dimension (in pixels) of the individual image 'cutout' 
	SDL_Point m_imageDimension;         //dimension (in pixels) of the image on the hard-drive (resolution)
	SDL_Point m_spriteDimension;        //dimension (in pixels) of the sprite image rendered on-screen

};

#endif