#pragma once
#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>

#include "Player.h"



class Game
{
public:
	Game();
	virtual ~Game();

	static int score;
	static int numOfPlayers;
	static int turnsCount;
	static bool isRunning;
	static bool firstPlay;
	static std::vector<Player*> playerList;

	static void start();
	static void gameLoop();
	static void exit();

	static void printPlayerList();
	static int randomStartSelector();
	static void determineNextTurn();


protected:

private:
};

#endif // GAME_H
