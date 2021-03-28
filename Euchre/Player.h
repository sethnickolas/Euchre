#pragma once
#include "Deck.h"
#include <string>
#include <iostream>
using namespace std;


class Player
{
public:
	Player(string setName, int pNumber, int theAggression);
	Player(const Player& obj);
	void setPosition(int);
	void setNextPosition();
	~Player();
	void getCards(Deck&);
	void printHand();
	string getName();
	void calcHandStrength(string flippedCard);
	bool isDealer();
	double getStrength();
	void setOrderUp(bool oU);
	void setDealerPickup(bool dP);
	void setNextPlayer(Player& nP);
	Player* getNextPlayer();
	int getPosition();
	void setDealer();
	void setDealerFalse();
	bool orderUpFunction();
	void removeWeakCard(string tCard);
	void bid();
	int getBestBidStrength();
	int getAggression();
	string getBestBidSuit();
	string playCard(string trumpCard);
	void createLegalMoves(string theLedSuit, string theTrump);
	void setLead(bool theLead);
	void printLegalMoves();
	void findBestMove();
	string getBestMove();

private:
	int playerNumber;
	string name;
	bool dealer;
	bool partnerDealer;
	string hand[5];
	string kitty[3];
	double winningPercentage;
	double handStrength;
	int aggression;  //might want to set defaults
	int position;
	bool orderUp;
	bool dealerPickup;
	Player* nextPlayer;
	//Player* playerPointer;
	friend class Game;
	int bestBidStrength;
	string bestBidSuit;
	string legalMoves[5];
	bool isLead;
	string bestMove;
};

