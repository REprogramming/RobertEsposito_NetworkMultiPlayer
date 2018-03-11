#pragma once 

#include "Player.h"
#include "Game.h"

Player::Player()
{
	createPlayer();
}

Player::~Player()
{
	//dtor
};

RakNet::SystemAddress g_serverAddress;
RakNet::RakPeerInterface *g_rakPeerInterface = nullptr;

void Player::createPlayer()
{
	int selection = 0;
	std::cout << "**************************************************" << std::endl;
	std::cout << "What is your characters name? " << std::endl;
	std::cin >> this->playerName;
	std::cout << "What will be your characters class? 0 = Warrior, 1 = Sorcerer, 2 = Rogue" << std::endl;
	std::cin >> selection;
	switch (selection)
	{
	case 0:
		characterClass = 0;
		characterClassName = "Warrior";
		health = 500;
		attackPower = 85;
		defendPower = 65;
		break;

	case 1:
		characterClass = 1;
		characterClassName = "Sorcerer";
		health = 300;
		attackPower = 65;
		defendPower = 85;
		break;

	case 2:
		characterClass = 2;
		characterClassName = "Rogue";
		health = 400;
		attackPower = 75;
		defendPower = 75;
		break;
	}

	std::cout << "Character Created: " << std::endl;
	std::cout << this->playerName << std::endl;
	std::cout << this->characterClassName << std::endl;
	std::cout << "**************************************************" << std::endl << std::endl;
	// TODO: SEND THIS DATA TO SERVER

}

void Player::doTurn()
{
	std::cout << playerName << " what action would you like to take? (0 = DEFEND, 1 = ATTACK, 2 = CHECK STATS) " << std::endl;
	int someAction;
	std::cin >> someAction;
	switch (someAction)
	{
	case 0: // Defend
		std::cout << playerName << " you are defending yourself." << std::endl;
		break;

	case 1: // Attack
		attack();
		break;

	case 2: // Check stats
		checkStats();
		break;
	}
}

void Player::attack()
{
	std::cout << playerName << " who do you wish to attack?" << std::endl;
	for (int i = 0; i < Game::playerList.size(); i++)
	{
		if (Game::playerList[i]->playerName == this->playerName)
		{
			// don't display
		}
		else
		{
			std::cout << "Target number: " << i << " -> " << Game::playerList[i]->playerName << std::endl;
		}
	}
	int targetNumber = 0;
	std::cout << "Enter the players target number you wish to attack..." << std::endl;
	std::cin >> targetNumber;
	std::cout << this->playerName << " is attacking " << Game::playerList[targetNumber]->playerName << std::endl;
	std::cout << this->playerName << " does " << this->attackPower << "HP of damage to " << Game::playerList[targetNumber]->playerName << std::endl;
	int calcDamage = Game::playerList[targetNumber]->health - this->attackPower;
	std::cout << Game::playerList[targetNumber]->playerName << " HP: " << calcDamage << std::endl;
	Game::determineNextTurn();
}

void Player::checkStats()
{
	std::cout << this->playerName << ":" << std::endl;
	std::cout << "Defend Power: " << this->defendPower << std::endl;
	std::cout << "Attack Power: " << this->attackPower << std::endl;
	std::cout << "Health: " << this->health << std::endl;
}

