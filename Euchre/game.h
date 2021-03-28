#pragma once
#include "Player.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void setPositions(Player pArray[4], int round);
	void setOrderUp();
	void setBidCall();
	bool getOrderUpStatus();
	bool getBidCallStatus();
	void clearStatus();
	void setTrump(string theTrump);
	string getTrump();
	void setLead(string theCard);
	string getLead();
	void incrementGameRound();
	int getGameRound();
	bool isGameOver();
	void setGameOver();
	void setPlayedCards(int playerNumber, string playedCard);
	void whoIsWinning(string playerMove, int counter);
	int evaluateRound();
	void clearPlayedCards();
	int getRoundScore(int inputNumber);

	//Player* getDealer(Player* pPointer);

private:
	bool gameOrderUp=false;
	bool gameBidCalled=false;
	string trump;
	string ledCard;
	int gameRound;
	bool gameOver;
	//string roundCards[4];
	string roundCards[4] = { "NULL","NULL","NULL","NULL"};
	int roundScore[4] = { -1,-1,-1,-1 };
};

