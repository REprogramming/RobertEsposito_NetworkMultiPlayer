#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include <iostream>

static int SERVER_PORT = 65000;
static int CLIENT_PORT = 65001;
static int MAX_CONNECTIONS = 4;

bool isServer = false;

int main()
{
	RakNet::RakPeerInterface* server = RakNet::RakPeerInterface::GetInstance();
	
		char userInput[255];
	std::cout << "Press (s) for server, (c) for client" << std::endl;
	std::cin >> userInput;
	isServer = userInput[0] == 's';
	
		if (isServer)
		{
		RakNet::SocketDescriptor socketDescriptors[1];
		socketDescriptors[0].port = SERVER_PORT;
		socketDescriptors[0].socketFamily = AF_INET;
		bool isSuccess = server->Startup(MAX_CONNECTIONS, socketDescriptors, 1) == RakNet::RAKNET_STARTED;
		assert(isSuccess);
		server->SetMaximumIncomingConnections(MAX_CONNECTIONS);
		std::cout << "server is up and running. type anything to exit." << std::endl;
		std::cin >> userInput;
		}
	
		return 0;
}