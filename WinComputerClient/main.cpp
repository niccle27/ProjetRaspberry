#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include<iostream>
#include <string>
#include "CommunicationManager.h"

using namespace std;

#define DEFAULT_PORT "51717"
#define DEFAULT_BUFLEN 32

#pragma comment(lib, "Ws2_32.lib")

int main() {
	cout << "mise a jour 3" << endl;
	CommunicationManager *toServer = new CommunicationManager();
	toServer->InitialiseWinsock();
	toServer->InitialiseServerAddr(AF_INET,51717, "192.168.1.11");
	toServer->CreateSocket();
	toServer->ConnectSocket();
	string bufferReceived;
	//toServer->Send("petit test de connection en objet");
	int result = toServer->Receive(bufferReceived);
	if (result > 0)
	{
		cout <<"received: "<< bufferReceived << endl;
		toServer->Send("bien recu");
	}
	toServer->CloseSocketConnection();
	delete toServer;
	system("pause");
	return 0;
	/*WSADATA wsaData;

	struct addrinfo *result = NULL,
		*ptr = NULL;

	SOCKET ConnectSocket = INVALID_SOCKET;

	char *sendbuf = (char*)"this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	SOCKADDR_IN  ServerAddr;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		system("pause");
		return 1;
	}
	// IPv4
	ServerAddr.sin_family = AF_INET;
	// Port no.
	ServerAddr.sin_port = htons(51717);
	// The IP address
	int serverNetworkIpAdress = 0;
	if(InetPton(AF_INET, "192.168.1.11", &serverNetworkIpAdress)==0)
	{
		std::cout << "error on using IntPton" << std::endl;
		return -1;
	}
	ServerAddr.sin_addr.s_addr = serverNetworkIpAdress;

	
	// Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM,0);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %d\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();//use to terminate the use of the WS2_32.dll
		return 1;
	}

	iResult = connect(ConnectSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}
	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	//iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("Bytes Sent: %d\n", iResult);
	// Receive data until the server closes the connection
	do {
		iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);

	return 0;*/
}