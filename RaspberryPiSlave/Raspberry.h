#pragma once
#include "CommunicationManager.h"
//#include <string.h>

#define DEFAULT_BUFLEN 40

using namespace std;
class Raspberry
{
private:
	CommunicationManager *communicationToComputer = new CommunicationManager();
public:
	int StartListeningForComputerConnection();
	std::string getReadingBufferComputerConnection();
	int SendComputerConnection(string bufferToSend);
public:
	Raspberry();
	~Raspberry();
};

