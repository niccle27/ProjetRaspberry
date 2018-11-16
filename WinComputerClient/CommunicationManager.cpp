#include "CommunicationManager.h"



int CommunicationManager::InitialiseWinsock()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		system("pause");
		return 0;
	}
	return 1;
}

int CommunicationManager::InitialiseServerAddr(int domain, int port, std::string ipAdress)
{
	// IPv4
	ServerAddr.sin_family = domain;//AF_INET
	// Port no.
	ServerAddr.sin_port = htons(port);//51717
	// The IP address
	int serverNetworkIpAdress = 0;
	if (InetPton(domain, ipAdress.c_str(), &serverNetworkIpAdress) == 0)//192.168.1.11
	{
		std::cout << "error on using IntPton" << std::endl;
		return 0;
	}
	ServerAddr.sin_addr.s_addr = serverNetworkIpAdress;
	return 1;
}

int CommunicationManager::CreateSocket()
{
	// Create a SOCKET for connecting to server
	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET) {
		printf("Error at socket(): %d\n", WSAGetLastError());
		//freeaddrinfo(result);
		WSACleanup();//use to terminate the use of the WS2_32.dll
		return 0;
	}
	return 1;
}

int CommunicationManager::CreateNonBlockingSocket()
{
	if(CreateSocket()==0)return 0;
	u_long mode = 1;//disable blocking
	int iResult = ioctlsocket(mSocket, FIONBIO,&mode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", iResult);
		return 0;
	}
	return 1;

}

bool CommunicationManager::IsSocketWritable()
{
	FD_SET writeSet;
	timeval timer;
	timer.tv_sec = 1;

	FD_ZERO(&writeSet);
	FD_SET(mSocket, &writeSet);
	select(0, nullptr, &writeSet, nullptr, &timer);
	return FD_ISSET(mSocket,&writeSet) != 0;
}

int CommunicationManager::ConnectSocket()
{
	int iResult = connect(mSocket, reinterpret_cast<SOCKADDR *>(&ServerAddr), sizeof(ServerAddr));
	if (iResult == SOCKET_ERROR) {
		//closesocket(mSocket);
		//mSocket = INVALID_SOCKET;
		return 0;
	}
	return 1;
}

int CommunicationManager::Send(std::string toBeSent)
{
	toBeSent.push_back('\0');
	char *sendbuf = (char*)toBeSent.c_str();
	// Send an initial buffer
	int iResult = send(mSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(mSocket);
		WSACleanup();
		return 0;
	}
	printf("Bytes Sent: %d\n", iResult);
	return 1;
}

int CommunicationManager::CloseSocketConnection()
{
	int iResult = shutdown(mSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(mSocket);
		WSACleanup();
		return 0;
	}
	return 1;
}

int CommunicationManager::Receive(std::string &bufferReceived)
{
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	iResult = recv(mSocket, recvbuf, DEFAULT_BUFLEN, 0);
	if (iResult > 0)
	{
		printf("Bytes received: %d\n", iResult);
		bufferReceived.assign(recvbuf, iResult);
	}
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());
	return iResult;
}

CommunicationManager::CommunicationManager()
{

}


CommunicationManager::~CommunicationManager()
{
}
