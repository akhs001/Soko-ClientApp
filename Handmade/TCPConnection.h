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
	
	void ReceiveThread();

	 bool OpenSocket() ;
	 bool Send(std::string& message) ;
	IPaddress& Get_ip() { return m_ip; }
	 bool Receive(std::string& message) ;
	 void SetState(PlayState* state) { m_state = state; }
	 void CloseSocket() {};

	void ShutDown();

private:
	IPaddress m_ip;
	std::string m_username;
	TCPsocket m_socket;
	SDLNet_SocketSet m_socketSet;
	PlayState* m_state;
};

