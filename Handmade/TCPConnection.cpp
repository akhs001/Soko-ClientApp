#include "TCPConnection.h"
#include <iostream>
#include <string>
#include "PlayState.h"



TCPConnection::TCPConnection()
{
	//Initialize the m_ip variable
	m_socketSet= SDLNet_AllocSocketSet(1);
	m_ip = { 0, 0 };

}


//Initialize the SDL And SDLNet
bool TCPConnection::Initialize(Uint16 port )
{
	//Initialize the SDL and SDLNet
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error initializing SDL" << std::endl;
		system("pause");
		return false;
	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Error initializing SDL net" << std::endl;
		system("pause");
		return false;
	}

	return true;
}

void TCPConnection::ReceiveThread()
{
	while (m_state->IsGameRunning)
	{



	}
}




bool TCPConnection::OpenSocket()
{
	//char address[30];
	std::string Address = "";

	char* result = InputBox( (char*)("Give the IP Address of the Server"),(char*)("Server IP Address") , (char*) ("127.0.0.1"));
	//std::cin >> address;

	if (SDLNet_ResolveHost(&m_ip, result, 1255) == -1)
	{
		std::cout << "Error Connecting to serverA" << std::endl;
		return false;
	}

	m_socket = SDLNet_TCP_Open(&m_ip);

	if (!m_socket)
	{
		std::cout << "Error Connecting to serverB" << std::endl;
		return false;
	}

	SDLNet_TCP_AddSocket(m_socketSet, m_socket);
	std::cout << "Connected to server" << std::endl;
}


bool TCPConnection::Send(std::string& message)
{
	
	if (SDLNet_TCP_Send(m_socket, message.c_str(), 15000))
	{
		return true;
	}
	return false;
}

bool TCPConnection::Receive(std::string& message)
{
	int haveMessage = SDLNet_CheckSockets(m_socketSet, 0);
	


	if (haveMessage > 0)
	{
		std::cout << haveMessage << std::endl;
		if (SDLNet_SocketReady(m_socket))
		{
			char data[15000];


				if (SDLNet_TCP_Recv(m_socket, &data, 15000) > 0)
				{
					
					message = data;
					if (message != "")
					{
						if (message[0] == 'L')
						{
							//Level received
							message = message.substr(1, message.length());
							m_state->StartGameS(message);
						}
						if (message[0] == 'P')			//Update all Movables Positions
						{
							//Movemtn received
							message = message.substr(1, message.length());
							m_state->UpdateMovables(message);
						}
						if (message[0] == 'M')			//Update all Movables Positions
						{
							//Movemtn received
							message = message.substr(1, message.length());
							m_state->UpdateServerPosition(message);
						}
						return true;
					}

				}
			
		}

	}
	return false;
}


void TCPConnection::ShutDown()
{
	//shutDown Sdl net
	SDLNet_Quit();

	//shutDown Sdl
	SDL_Quit();
}
