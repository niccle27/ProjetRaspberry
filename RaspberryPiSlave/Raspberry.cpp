#include "Raspberry.h"
#include <string.h>

int Raspberry::StartListeningForComputerConnection()
{
	return communicationToComputer->StartListeningForConnection();
}

std::string Raspberry::getReadingBufferComputerConnection()
{
	string temp;
	char test[DEFAULT_BUFLEN];
	cout << "test" << endl;
	int result = communicationToComputer->ReadData(test);
	temp.assign(test, strlen(test));
	return temp;
}

int Raspberry::SendReadingBufferComputerConnection(string bufferToSend)
{
	return communicationToComputer->SendData(bufferToSend);
}

Raspberry::Raspberry()
{

}


Raspberry::~Raspberry()
{
	delete communicationToComputer;
}
