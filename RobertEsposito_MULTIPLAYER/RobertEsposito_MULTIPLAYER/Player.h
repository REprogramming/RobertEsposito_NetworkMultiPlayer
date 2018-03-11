#pragma once 
#ifndef PLAYER_H
#define PLAYER_H



#include<iostream>
#include<string>




class Player
{
public:
	Player();
	virtual ~Player();

	int playerID;
	std::string playerName;
	int characterClass;
	std::string characterClassName;
	int health;
	int attackPower;
	int defendPower;	

	void createPlayer();
	void attack();
	void defend();
	void checkStats();
	void doTurn();


protected:

private:
};

#endif // PLAYER_H
