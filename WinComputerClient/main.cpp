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
	toServer->CreateNonBlockingSocket();
	bool flag = true;
	while (flag)
	{
		if (toServer->IsSocketWritable())
		{
			break;
		}
		int result = toServer->ConnectSocket();
		if(result == 1)
		{
			flag = false;
		}
		else cout << "waiting" << endl;
	}	
	string bufferReceived;
	while(true)
	{
		int result = toServer->Receive(bufferReceived);		
		if (result > 0)
		{
			cout <<"received: "<< bufferReceived << endl;
			toServer->Send("bien recu");
			break;
		}
		cout << "on peut faire autre chose " << endl;
	}

	toServer->CloseSocketConnection();
	delete toServer;
	system("pause");
	return 0;
}