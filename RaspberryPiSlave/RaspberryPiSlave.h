#pragma once
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define DEFAULT_BUFLEN 32
#define PORT 51717
class RaspberryPiSlave
{
	//method
public:
	RaspberryPiSlave();
	~RaspberryPiSlave();
	void StartListeningForConnection();
//private:
	void SendData(char data[]);
	char* ReadData();
	
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

};



