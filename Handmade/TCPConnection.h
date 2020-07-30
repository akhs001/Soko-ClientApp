#pragma once
#include <string>
#include <SDL.h>
#include <SDL_net.h>
#include <vector>
#include "InputBox.h"


class PlayState;

class TCPConnection
{
public:
	TCPConnection();


public :
	bool Initialize(Uint16 port);
	

	 bool OpenSocket() ;
	 bool Send(std::string& message) ;
	 IPaddress& Get_ip();
	 bool Receive(std::string& message) ;
	 void SetState(PlayState* state);
	 void CloseSocket() {};

	void ShutDown();

private:
	TCPsocket m_socket;
	IPaddress m_ip;

	SDLNet_SocketSet m_socketSet;
	PlayState* m_state;
};

