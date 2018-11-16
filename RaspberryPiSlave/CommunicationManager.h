#pragma once
#include <wiringPi.h>
#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
using namespace std;
#define PORT 51717
#define DEFAULT_BUFLEN 32
class CommunicationManager
{
	//method
public:
	CommunicationManager();
	~CommunicationManager();
	int StartListeningForConnection();
//private:
	int SendData(string toBeSent);
	int ReadData(string &buffer);
	
	//static method
public:
private:
	static void Error(char *msg);
	static int OpenSocket(int domain, int type, int protocol);
	//field
public:
private:
	int socketListening;
	int socketStream;//TODO close the sockets
	int port = PORT;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;;
	//char buffer[DEFAULT_BUFLEN];

};



