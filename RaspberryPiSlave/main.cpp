#include "CommunicationManager.h"
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
// we have to use BCM numbering when initializing with wiringPiSetupSys
// when choosing a different pin number please use the BCM numbering, also
// update the Property Pages - Build Events - Remote Post-Build Event command 
// which uses gpio export for setup for wiringPiSetupSys
#define	LED	17

int main(void)
{
	wiringPiSetupSys();
	std::cout << "version mise a jour 10" << std::endl;
	CommunicationManager *toComputer = new CommunicationManager();
	toComputer->StartListeningForConnection();
	toComputer->SendData("test envoi depuis rapsberry");
	string received;
	toComputer->ReadData(received);
	cout << "received: " << received << endl;
	/*Raspberry *raspberry = new Raspberry();
	raspberry->StartListeningForComputerConnection();
	raspberry->SendComputerConnection("test envoi depuis raspberry");
	string received = raspberry->getReadingBufferComputerConnection();
	cout << "received" << received << endl;*/

}