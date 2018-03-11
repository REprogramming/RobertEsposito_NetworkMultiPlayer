#include "Game.h"


Game::Game()
{
	start();
}

Game::~Game()
{
	//dtor
}

void Game::start()
{
	std::cout << "Starting game..." << std::endl;
	std::cout << "Number of Players:" << std::endl;
	std::cin >> Game::numOfPlayers;
	std::cout << std::endl;

	for (int i = 0; i < Game::numOfPlayers; i++)
	{
		Player* _Player = new Player();
		Game::playerList.push_back(_Player);
	}

	std::cout << std::endl;

	Game::gameLoop();
}

void Game::gameLoop()
{
	std::cout << "///////////////////////////////////" << std::endl;
	std::cout << "Battle ground created - Let's begin!" << std::endl;
	std::cout << "///////////////////////////////////" << std::endl << std::endl;
	printPlayerList();
	if (firstPlay == false)
	{
		int playerStartGenerator = Game::randomStartSelector();
		std::cout << "..................................." << std::endl;
		std::cout << "Random start: " << playerList[playerStartGenerator]->playerName << " will go first." << std::endl << "Goodluck!" << std::endl;
		std::cout << "..................................." << std::endl << std::endl;
		playerList[playerStartGenerator]->doTurn();
		firstPlay == true;
	}
}

void Game::exit()
{

}

void Game::printPlayerList()
{
	std::cout << "Size of player list: " << Game::playerList.size() << std::endl << std::endl;
	for (int i = 0; i < playerList.size(); i++)
	{
		std::cout << playerList[i]->playerName << " = " << playerList[i]->characterClassName << std::endl;
		std::cout << " HP:" << playerList[i]->health << std::endl << " Attack Power:" << playerList[i]->attackPower << std::endl << " Defend Power:" << playerList[i]->defendPower << std::endl << std::endl;
	}
}

int Game::randomStartSelector()
{
	int randNum = rand() % playerList.size();
	Game::turnsCount = randNum;
	return randNum;
}

void Game::determineNextTurn()
{
	Game::turnsCount++;
	if (Game::turnsCount >= playerList.size())
	{
		Game::turnsCount = 0;
	}

	std::cout << std::endl << std::endl;
	std::cout << "******NEXT TURN*******" << std::endl;
	std::cout << playerList[turnsCount]->playerName << " get ready..." << std::endl;
	playerList[turnsCount]->doTurn();

}


