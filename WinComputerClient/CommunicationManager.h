#pragma once

#include <winsock2.h>
#include <string>
#include <cstdio>
#include <ostream>
#include <iostream>
#include <ws2tcpip.h>

#define DEFAULT_BUFLEN 32

class CommunicationManager
{
private:
	WSADATA wsaData;
	SOCKET mSocket = INVALID_SOCKET;
	SOCKADDR_IN  ServerAddr;
public:
	int InitialiseWinsock();
	int InitialiseServerAddr(int domain, int port, std::string ipAdress);
	int CreateSocket();
	int ConnectSocket();
	int Send(std::string toBeSent);
	int CloseSocketConnection();
	int Receive(std::string &bufferReceived);


public:
	CommunicationManager();
	~CommunicationManager();
};

