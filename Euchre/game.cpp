#include "pch.h"
#include "game.h"


Game::Game()
{
	trump = "NULL";
	ledCard = "NULL";
	gameRound = 0;
	gameOver = false;
}


Game::~Game()
{
}

void Game::setPositions(Player pArray[4], int round) {

}

void Game::setOrderUp(){
	gameOrderUp = true;
}

bool Game::getOrderUpStatus() {
	return(gameOrderUp);
}

void Game::clearStatus() {
	gameOrderUp = false;
	gameBidCalled = false;
}

void Game::setTrump(string theTrump) {
	trump = theTrump;
}

void Game::setBidCall() {
	gameBidCalled = true;
}

string Game::getTrump() {
	return(trump);
}

bool Game::getBidCallStatus() {
	return(gameBidCalled);
}

void Game::setLead(string theCard) {
	ledCard = theCard;
}

string Game::getLead() {
	return(ledCard);
}

void Game::incrementGameRound() {
	++gameRound;
}

int Game::getGameRound() {
	return(gameRound);
}

bool Game::isGameOver() {
	return(gameOver);
}

void Game::setGameOver() {
	gameOver = true;
}

void Game::setPlayedCards(int playerNumber, string playedCard) {
	roundCards[playerNumber] = playedCard;
}

void Game::whoIsWinning(string playerMove, int counter) {
	roundCards[counter] = playerMove;
	string playerMoveSuit;
	playerMoveSuit = playerMove[1];
	
	string playerMoveRank;
	playerMoveRank = playerMove[0];
	
	string ledCardSuit;
	ledCardSuit = ledCard[1];

	//cout << endl << "RoundCards" << roundCards[counter] << endl;
	//we know trump, and we know the led card
	for (int i = 0; i < 4; i++) {
		if (playerMove != "NULL") {
			
			//it is trump
			if (playerMoveSuit == trump) {
				if (playerMoveRank == "N") {
					roundScore[counter] = 7;
				}
				else if (playerMoveRank == "T") {
					roundScore[counter] = 8;
				}
				else if (playerMoveRank == "Q") {
					roundScore[counter] = 9;
				}
				else if (playerMoveRank == "K") {
					roundScore[counter] = 10;
				}
				else if (playerMoveRank == "A") {
					roundScore[counter] = 11;
				}
				else if (playerMoveRank == "J") {
					roundScore[counter] = 13;
				}
			}

			//it is the left
			else if ((playerMove == "JD" && trump == "H") || (playerMove == "JH" && trump == "D") || (playerMove == "JC" && trump == "S") || (playerMove == "JS" && trump == "C") ) {
				roundScore[counter] = 12;
			}

			//it is the led suit
			else if (playerMoveSuit == ledCardSuit) {
				if (playerMoveRank == "N") {
					roundScore[counter] = 1;
				}
				else if (playerMoveRank == "T") {
					roundScore[counter] = 2;
				}
				else if (playerMoveRank == "J") {
					roundScore[counter] = 3;
				}
				else if (playerMoveRank == "Q") {
					roundScore[counter] = 4;
				}
				else if (playerMoveRank == "K") {
					roundScore[counter] = 5;
				}
				else if (playerMoveRank == "A") {
					roundScore[counter] = 6;
				}
			}

			//they threw off suit
			else {
				roundScore[counter] = 0;
			}

		}

		//there is no card
		else
		{
			roundScore[i] = -1;
		}

	}

}


int Game::evaluateRound() {
	//find highest trump, else get highest led card suit
	return(0);

}

void Game::clearPlayedCards() {
	roundCards[0] = "NULL";
	roundCards[1] = "NULL";
	roundCards[2] = "NULL";
	roundCards[3] = "NULL";
}


int Game::getRoundScore(int inputNumber) {
	return(roundScore[inputNumber]);
}

/*Player* Game::getDealer(Player* pPointer) {
	
	for (int j = 0; j < 4; j++) {
		if (pPointer[j].isDealer() == true) {

		}
	}
}*/