#include "Raspberry.h"


int Raspberry::StartListeningForComputerConnection()
{
	return communicationToComputer->StartListeningForConnection();
}

std::string Raspberry::getReadingBufferComputerConnection()
{
	return std::string(communicationToComputer->ReadData());
}

void Raspberry::SendData(char data[])
{
	communicationToComputer->SendData(data);
}

Raspberry::Raspberry()
{

}


Raspberry::~Raspberry()
{
}
