#include "Debug.h"
#include "Sound.h"

std::map<std::string, Mix_Chunk*>* Sound::s_sounds = new std::map<std::string, Mix_Chunk*>;

//------------------------------------------------------------------------------------------------------
//static function that loads sound audio data from a raw audio file 
//first check if sound data exists in map and if it does display warning message
//and halt loading because we don't want to replace the existing sound data
//otherwise, load sound data from file using SDL audio load function 
//and if sound loading failed, display error message, else add it to the map
//------------------------------------------------------------------------------------------------------
bool Sound::Load(const std::string& filename, const std::string& mapIndex)
{

	Debug::Log("Opening and reading sound file: '" + filename + "'");

	if (s_sounds->find(mapIndex) != s_sounds->end())
	{
		Debug::Log("Sound data already loaded in memory.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());

	if (!sound)
	{
		Debug::Log("File could not be loaded.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}
	
	(*s_sounds)[mapIndex] = sound;

	Debug::Log("File opened and read successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	return true;

}
//------------------------------------------------------------------------------------------------------
//static function that unloads single or multiple sound data from memory
//if the 'mapIndex' string is empty it means we need to remove all sound data
//otherwise it means a specific ID has been passed which indicates 
//that specific sound data should be removed. In that case, we first see
//if it is in the map before removing it
//------------------------------------------------------------------------------------------------------
void Sound::Unload(const std::string& mapIndex)
{

	if (!mapIndex.empty())
	{

		Debug::Log("Unloading sound data: '" + mapIndex + "'");

		auto it = s_sounds->find(mapIndex);

		if (it == s_sounds->end())
		{
			Debug::Log("Sound data not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
			Debug::Log("===============================================================");
		}

		else
		{
			Mix_FreeChunk(it->second);
			s_sounds->erase(it);

			Debug::Log("Sound data unloaded successfully.", Debug::ErrorCode::SUCCESS);
			Debug::Log("===============================================================");
		}
	}

	else
	{

		Debug::Log("Unloading all sound data.");

		for (auto it = s_sounds->begin(); it != s_sounds->end(); it++)
		{
			Mix_FreeChunk(it->second);
		}

		s_sounds->clear();

		Debug::Log("All sound data unloaded successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");

	}

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sound::Sound()
{

	m_sound = nullptr;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets volume of sound 
//------------------------------------------------------------------------------------------------------	
void Sound::SetVolume(int volume)
{

	Mix_VolumeChunk(m_sound, volume);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns sound object based on index value passed
//first we must check if sound data exists in map and if not display
//warning message, otherwise go ahead and assign the handle
//------------------------------------------------------------------------------------------------------
bool Sound::SetSound(const std::string& mapIndex)
{

	auto it = s_sounds->find(mapIndex);

	if (it == s_sounds->end())
	{
		Debug::Log("Sound data not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	m_sound = (*it).second;
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that plays the sound effect on first available free channel
//play the sound on a loop cycle (if appropriate) based on 'loop' argument passed
//if playing sound effect fails, display error message and return false for client code to handle
//------------------------------------------------------------------------------------------------------
bool Sound::Play(int loop)
{

	if (Mix_PlayChannel(-1, m_sound, loop) == -1)
	{
		Debug::Log("Sound could not be played.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	return true;

}