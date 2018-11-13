#pragma once
#include "CommunicationManager.h"
#include "string"
class Raspberry
{
private:
	CommunicationManager *communicationToComputer = new CommunicationManager();
public:
	int StartListeningForComputerConnection();
	std::string getReadingBufferComputerConnection();
	void SendData(char data[]);
public:
	Raspberry();
	~Raspberry();
};

