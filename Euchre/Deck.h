#pragma once
#include <string>
#include <iostream>
#include "time.h"

using namespace std;

class Deck
{
public:
	Deck();
	~Deck();
	void shuffleCards();
	void printDeck();
	void setTurnCard();
	string getTurnCard();
	void printTurnCard();
	static const int NUMCARDS = 24;

private:
	string cards[NUMCARDS];
	string turnCard;
	friend class Player;
	friend class Game;
};


