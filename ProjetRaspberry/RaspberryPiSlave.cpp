#include "RaspberryPiSlave.h"



RaspberryPiSlave::RaspberryPiSlave()
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
RaspberryPiSlave::~RaspberryPiSlave()
{
	close(socketListening);
	close(socketStream);
}

void RaspberryPiSlave::Error(char* msg)
{
	std::cerr << msg << std::endl;
	exit(1);
}

void RaspberryPiSlave::SendData(char data[])
{
	if (int socket = NULL)
	{
		std::cerr << "Socket is null, failed to send data" << std::endl;
		return;
	}
	int n;
	char buffer[DEFAULT_BUFLEN];
	strncpy(buffer, data, strlen(data));
	if ((n = write(socketStream, buffer, strlen(buffer))) < 0)
		Error(const_cast<char *>("ERROR writing to socket"));
	//buffer[n] = '\0';
}

char* RaspberryPiSlave::ReadData()
{
	if (int socket = NULL)
	{
		std::cerr << "Socket is null, failed to send data" << std::endl;
		return nullptr;
	}
	char buffer[DEFAULT_BUFLEN];
	int n=read(socketStream, buffer, DEFAULT_BUFLEN - 1);
	if (n < 0)
	{
		Error(const_cast<char *>("ERROR reading from socket"));
		return nullptr;
	}

	else if (n == 0) return nullptr;
	else
	{
		buffer[n] = '\0';
		std::cout << buffer << std::endl;
		return buffer;
	}

}

void RaspberryPiSlave::StartListeningForConnection()
{
	while (true) {
		printf("waiting for new client...\n");
		int clientLength = sizeof(cli_addr);
		if ((socketStream = accept(socketListening, reinterpret_cast<struct sockaddr *>(&cli_addr), reinterpret_cast<socklen_t*>(&clientLength))) < 0)  // NOLINT(android-cloexec-accept)
			Error("ERROR on accept");
		printf("opened new communication with client\n");
		break;
	}
}


int RaspberryPiSlave::OpenSocket(int domain, int type, int protocol)
{
	int tmp = socket(domain, type, protocol);
	if (tmp < 0)
		Error(const_cast<char *>("ERROR opening socket"));
	return tmp;
}

