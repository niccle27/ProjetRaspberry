#include "CommunicationManager.h"
#include <string.h>
using namespace std;

CommunicationManager::CommunicationManager()
{
	this->socketListening = OpenSocket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);// convert portno from host byte order to network byte order
	if(bind(socketListening,reinterpret_cast<struct sockaddr *>(&serv_addr),sizeof(serv_addr))<0)
	{
		Error("Error occured on binding listening socket");
	}
	listen(socketListening, 1);//prepare to listen on sockfd, 5 attempt will be queued before refusing the others
}
CommunicationManager::~CommunicationManager()
{
	close(socketListening);
	close(socketStream);
}

void CommunicationManager::Error(char* msg)
{
	std::cerr << msg << std::endl;
	exit(1);
}

int CommunicationManager::SendData(string toBeSent)
{
	toBeSent.push_back('\0');
	char *sendbuf = (char*)toBeSent.c_str();
	if (int socket = NULL)
	{
		std::cerr << "Socket is null, failed to send data" << std::endl;
		return 0;
	}
	int n;
	/*char buffer[DEFAULT_BUFLEN];
	strncpy(buffer, data, strlen(data));*/
	if ((n = write(socketStream, sendbuf, strlen(sendbuf))) < 0)
	{
		Error(const_cast<char *>("ERROR writing to socket"));
		return 0;
	}
	//buffer[n] = '\0';
	return n;
}

int CommunicationManager::ReadData(string &buffer)
{
	char bufferReceived[DEFAULT_BUFLEN];
	if (socketStream == NULL){
		std::cerr << "Socket is null, failed to read data" << std::endl;
		return 0;
	}
	int nbrBitReceived=read(socketStream, bufferReceived, 40);
	if (nbrBitReceived < 0)
	{
		Error(const_cast<char *>("ERROR reading from socket"));
		return 0;
	}
	else if (nbrBitReceived == 0) return 0;
	else
	{
		//dataReceived
		bufferReceived[nbrBitReceived] = '\0';
		buffer.assign(bufferReceived, nbrBitReceived);
		//std::cout << bufferReceived << std::endl;
		return 1;
	}

}

int CommunicationManager::StartListeningForConnection()
{
	while (true) {
		printf("waiting for new client...\n");
		int clientLength = sizeof(cli_addr);
		if ((socketStream = accept(socketListening, reinterpret_cast<struct sockaddr *>(&cli_addr), reinterpret_cast<socklen_t*>(&clientLength))) < 0)  // NOLINT(android-cloexec-accept)
		{
			Error("ERROR on accept");
			return 0;	
		}
		printf("opened new communication with client\n");
		return 1;
	}
}


int CommunicationManager::OpenSocket(int domain, int type, int protocol)
{
	int tmp = socket(domain, type, protocol);
	if (tmp < 0)
		Error(const_cast<char *>("ERROR opening socket"));
	return tmp;
}

