#include "Music.h"
#include "Debug.h"

std::map<std::string, Mix_Music*>* Music::s_music = new std::map<std::string, Mix_Music*>;

//------------------------------------------------------------------------------------------------------
//static function that initializes SDL audio sub-system 
//if audio sub-system initialization failed, display error message and return false
//------------------------------------------------------------------------------------------------------
bool Music::Initialize(int frequency, int chunkSize)
{

	Debug::Log("Initializing audio sub-system...");

	if (Mix_OpenAudio(frequency, AUDIO_S16SYS, 2, chunkSize) == -1)
	{
		Debug::Log("Audio sub-system did not initialize properly.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	Debug::Log("Audio sub-system successfully setup", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	return true;

}
//------------------------------------------------------------------------------------------------------
//static function that loads music audio data from a raw audio file 
//first check if music data exists in map and if it does display warning message
//and halt loading because we don't want to replace the existing music data
//otherwise, load music data from file using SDL audio load function 
//and if music loading failed, display error message, else add it to the map
//------------------------------------------------------------------------------------------------------
bool Music::Load(const std::string& filename, const std::string& mapIndex)
{

	Debug::Log("Opening and reading music file: '" + filename + "'");

	if (s_music->find(mapIndex) != s_music->end())
	{
		Debug::Log("Music data already loaded in memory.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}
	
	Mix_Music* music = Mix_LoadMUS(filename.c_str());

	if (!music)
	{
		Debug::Log("File could not be loaded.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	(*s_music)[mapIndex] = music;
	
	Debug::Log("File opened and read successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	return true;

}
//------------------------------------------------------------------------------------------------------
//static function that unloads single or multiple music data from memory
//if the 'mapIndex' string is empty it means we need to remove all music data
//otherwise it means a specific ID has been passed which indicates 
//that specific music data should be removed. In that case, we first see
//if it is in the map before removing it
//------------------------------------------------------------------------------------------------------
void Music::Unload(const std::string& mapIndex)
{

	if (!mapIndex.empty())
	{

		Debug::Log("Unloading music data: '" + mapIndex + "'");

		auto it = s_music->find(mapIndex);

		if (it == s_music->end())
		{
			Debug::Log("Music data not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
			Debug::Log("===============================================================");
		}

		else
		{
			Mix_FreeMusic(it->second);
			s_music->erase(it);

			Debug::Log("Music data unloaded successfully.", Debug::ErrorCode::SUCCESS);
			Debug::Log("===============================================================");
		}
	}

	else 
	{

		Debug::Log("Unloading all music data.");

		for (auto it = s_music->begin(); it != s_music->end(); it++)
		{
			Mix_FreeMusic(it->second);
		}

		s_music->clear();

		Debug::Log("All music data unloaded successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");

	}

}
//------------------------------------------------------------------------------------------------------
//static function that closes down SDL audio sub-system
//------------------------------------------------------------------------------------------------------
void Music::ShutDown()
{

	Mix_CloseAudio();

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Music::Music()
{

	m_music = nullptr;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets volume of audio
//------------------------------------------------------------------------------------------------------
void Music::SetVolume(int volume)
{

	Mix_VolumeMusic(volume);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns music object based on index value passed
//first we must check if music data exists in map and if not display
//warning message, otherwise go ahead and assign the handle
//------------------------------------------------------------------------------------------------------
bool Music::SetMusic(const std::string& mapIndex)
{

	auto it = s_music->find(mapIndex);

	if (it == s_music->end())
	{
		Debug::Log("Music data not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	m_music = (*it).second;
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that plays music. We check if music is not already playing and if not we play the
//music on a repeat cycle (if any), based on 'loopType'. If playing music fails, display error 
//message and return 'false' flag for the client code to handle
//------------------------------------------------------------------------------------------------------
bool Music::Play(LoopType loopType)
{

	if(!Mix_PlayingMusic())
	{
		if(Mix_PlayMusic(m_music, static_cast<int>(loopType)) == -1)
		{
			Debug::Log("Music could not be played.", Debug::ErrorCode::FAILURE);
			Debug::Log("===============================================================");
			return false;
		}
	}
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that pauses the playing music. First check if music is not already paused
//------------------------------------------------------------------------------------------------------
void Music::Pause()
{

	if(!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}

}
//------------------------------------------------------------------------------------------------------
//function that resumes the music after a paused state. First check if music is paused
//------------------------------------------------------------------------------------------------------
void Music::Resume()
{

	if(Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}

}
//------------------------------------------------------------------------------------------------------
//function that stops playing music. First check if music is playing
//------------------------------------------------------------------------------------------------------
void Music::Stop()
{

	if(Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}

}