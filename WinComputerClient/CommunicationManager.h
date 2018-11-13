#pragma once
#define DEFAULT_BUFLEN 32
#include <winsock2.h>
#include <string>
#include <cstdio>
#include <ostream>
#include <iostream>
#include <ws2tcpip.h>

class CommunicationManager
{
private:
	WSADATA wsaData;
	SOCKET mSocket = INVALID_SOCKET;
	char recvbuf[DEFAULT_BUFLEN];
	SOCKADDR_IN  ServerAddr;
public:
	int InitialiseWinsock();
	int InitialiseServerAddr(int domain, int port, std::string ipAdress);
	int CreateSocket();
	int ConnectSocket();
	int Send(std::string toBeSent);
	int CloseSendingConnection();
	int WaitAndReceive();


public:
	CommunicationManager();
	~CommunicationManager();
};

