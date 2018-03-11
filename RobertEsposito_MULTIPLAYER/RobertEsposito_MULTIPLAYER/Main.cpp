#pragma once

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "BitStream.h"

#include "Game.h"
#include "Player.h"

#include<iostream>
#include<thread>
#include<chrono>
#include<map>
#include<string>
#include<vector>
#include<stdlib.h>
#include<time.h>

#include <stdio.h>
#include <string.h>
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID

static unsigned int MAX_CLIENTS = 10;
static unsigned int SERVER_PORT = 60000;

// static initialization
int Game::score = 0;
int Game::numOfPlayers = 0;
int Game::turnsCount = 0;
bool Game::isRunning = true;
bool Game::firstPlay = false;
std::vector<Player*> Game::playerList;

enum GameMessages
{
	ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1, ID_GAME_MESSAGE_2 = ID_USER_PACKET_ENUM + 2, ID_PLAYER_READY
};

void SendName(int playerID, RakNet::SystemAddress systemAddress, bool isBroadcast)
{
	RakNet::BitStream writeBs;
	writeBs.Write((RakNet::MessageID)ID_PLAYER_READY);
	RakNet::RakString name(Game::playerList[playerID]->playerName.c_str());
	writeBs.Write(name);


	//returns 0 when something is wrong
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	assert(peer->Send(&writeBs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemAddress, isBroadcast));
}



int main(void)
{
	char str[512];	
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	bool isServer;
	RakNet::Packet *packet;


	printf("(C) or (S)erver?\n");
	gets_s(str);

	if ((str[0] == 'c') || (str[0] == 'C'))
	{
		RakNet::SocketDescriptor sd;
		peer->Startup(1, &sd, 1);
		isServer = false;
	}
	else {
		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		peer->Startup(MAX_CLIENTS, &sd, 1);
		isServer = true;
	}

	if (isServer)
	{
		// SERVER SCREEN
		printf("Starting the server.\n");
		// We need to let the server accept incoming connections from the clients
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);		
	}
	else 
	{
		// CLIENT SCREEN
		printf("Enter server IP or hit enter for 127.0.0.1\n");
		gets_s(str);
		if (str[0] == 0) {
			strcpy_s(str, "127.0.0.1");
		}
		printf("Starting the client.\n");
		peer->Connect(str, SERVER_PORT, 0, 0);
	}

	while (1)
	{
		char userInput[255]; 
		for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{	// CLIENT SCREEN
				printf("Our connection request has been accepted.\n");

				std::cout << "Enter your username to play or type quit to leave." << std::endl;
				std::cin >> userInput;
				assert(strcmp(userInput, "quit"));

				// Player Creation - Begin play...
				Player* _Player = new Player();
				Game::numOfPlayers++; 
				Game::playerList.push_back(_Player);
				_Player->playerID = Game::numOfPlayers; 
				_Player->playerName = userInput; 
				std::cout << "Player created " << _Player->playerName << std::endl; 	
				
				// Use a BitStream to write to server
				// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
				RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
				RakNet::RakString name(_Player->playerName.c_str());
				bsOut.Write(name + " has joined.");			
				peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
				
				// TODO: Send back a msg to all players from Server
				RakNet::BitStream bsOut2;
				bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
				RakNet::RakString data(std::to_string(Game::numOfPlayers).c_str());
				bsOut2.Write( data + " Total Players.");
				peer->Send(&bsOut2, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);							
			}
			break;
			case ID_NEW_INCOMING_CONNECTION:
				printf("A connection is incoming.\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (isServer) {
					printf("A client has disconnected.\n");
				}
				else {
					printf("We have been disconnected.\n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (isServer) {
					printf("A client lost the connection.\n");
				}
				else {
					printf("Connection lost.\n");
				}
				break;

			case ID_GAME_MESSAGE_1:
			{
				RakNet::RakString rs;
				RakNet::BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				bsIn.Read(rs);
				printf("%s\n", rs.C_String());				
			}
		
			break;

			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}


	RakNet::RakPeerInterface::DestroyInstance(peer);

	return 0;
}

