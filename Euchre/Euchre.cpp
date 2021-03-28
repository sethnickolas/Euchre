// Euchre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Deck.h"
#include "Player.h"
#include "game.h"
#include <iostream>
#include <list>


using namespace std;

//helper functions that might need to go into a class later
void printDealerHelper(Player helperPlayers[4]);
void dealCards(Player helperPlayers[4], Deck &helperDeck);
void handStr(Player helperPlayers[4], string fCard);
void printHelper(Player helperPlayers[4]);
bool dealerPickUp(Player &dealerPlayer);
string suitAbbreviation(string theSuit);
int roundConverter(const int &theRound);
static int testRoundLimit = 1;


int main()
{

	/*Initialize the players*/
	/*Player playerOne("AJ", 1);
	Player playerTwo("Jon", 2);
	Player playerThree("Kevin", 3);
	Player playerFour("Nick", 4);*/
	Player* playerPointer = nullptr;

	/*Create Player Array, assigning each player a "playernumber" which
	is slightly irrelevant*/
	Player playerArray[4] = { {"AJ",1,8},{"Jon",2,8},{"Kevin",3,8},{"Nick",4,8} };

	/*Set the next player link so we have a pointer from every player to the next
	player*/
	for (int i = 0; i < 4; i++) {
		if (i != 3) {
			playerArray[i].setNextPlayer(playerArray[i + 1]);
		}
		else {
			playerArray[i].setNextPlayer(playerArray[0]);
		}
	}

	//Build the deck
	Deck myDeck;

	//Build the game
	Game myGame;

	//TESTING PURPOSES:  Set # of rounds
	
	int testRoundCounter = 0;
	while (!myGame.isGameOver())
	{
		myGame.incrementGameRound();
			
		//Shuffle the cards
			myDeck.shuffleCards();

			//turnCard for the deck is set to the 20th card
			myDeck.setTurnCard();

			/*Initialize the positions -- player position depends on the
			"playernumber" and number of rounds*/

			cout << endl << endl << " -- Round " << myGame.getGameRound() << " --";

			//set the next positions if we're after round 1
			if (myGame.getGameRound() != 1) {
				playerArray[0].setNextPosition();
				cout << endl << playerArray[0].getName() << " position is:" << playerArray[0].getPosition();
				playerArray[1].setNextPosition();
				cout << endl << playerArray[1].getName() << " position is:" << playerArray[1].getPosition();
				playerArray[2].setNextPosition();
				cout << endl << playerArray[2].getName() << " position is:" << playerArray[2].getPosition();
				playerArray[3].setNextPosition();
				cout << endl << playerArray[3].getName() << " position is:" << playerArray[3].getPosition();
			}

			//set position 1 as the dealer and have a pointer to them
			Player* dealerPointer = nullptr;
			for (int j = 0; j < 4; j++) {
				if (playerArray[j].getPosition() == 1) {
					playerArray[j].setDealer();
					dealerPointer = &playerArray[j];
				}
			}


			/*-------------Start the game----------------------------------------*/

			/*Print the name of the Dealer*/
			printDealerHelper(playerArray);

			/*Deal Cards*/
			dealCards(playerArray, myDeck);

			/*print turn card*/
			myDeck.printTurnCard();

			/*calculate the hands strength based on the top card*/
			handStr(playerArray, myDeck.getTurnCard());

			/*print the cards for each player*/
			printHelper(playerArray);

			/* for left of dealer, order or pass*/

			//need to use playerArray.getPosition to determine who starts


			int a = 0;
			while (a < 4) {
				if (a == 0) {
					playerPointer = dealerPointer->getNextPlayer();
				}
				else {
					playerPointer = playerPointer->getNextPlayer();
				}
				if (playerPointer->orderUpFunction()) {
					cout << endl << playerPointer->getName() << " ordered it up";
					myGame.setOrderUp();
				}
				else
				{
					cout << endl << playerPointer->getName() << " passed.";
				}
				if (myGame.getOrderUpStatus() == true) { a = 3; }
				a++;
			}

			/*for (int j = 0; j < 4; j++) {
				playerPointer = playerArray[j].getNextPlayer();
				if (playerPointer->orderUpFunction()) {
					cout << endl << playerPointer->getName() << " ordered it up";
					myGame.setOrderUp();
				}
				else
				{
					cout << endl << playerPointer->getName() << " passed.";
				}
				if (myGame.getOrderUpStatus() == true) { j = 4; }
			}*/

			/****************** Ordered Up ******************/
			/* if turn card is ordered up */
			if (myGame.getOrderUpStatus() == true) {
				/* if ordered up, set trump as the turn card*/
				string tempTrumpCard = myDeck.getTurnCard();
				tempTrumpCard = tempTrumpCard[1];
				myGame.setTrump(tempTrumpCard);

				/*, the dealer needs to remove a card*/
				playerPointer = dealerPointer;
				dealerPointer->removeWeakCard(myDeck.getTurnCard());
			}

			/* if nobody ordered it up, then bid*/
			else {
				for (int j = 0; j < 4; j++) {
					playerPointer = playerArray[j].getNextPlayer();
					playerPointer->bid();
					if (playerPointer[j].getBestBidStrength() > playerPointer->getAggression()) {

						//string trump = suitAbbreviation(playerPointer[j].getBestBidSuit());  //returns full suit name
						string trump = playerPointer[j].getBestBidSuit();

						myGame.setTrump(trump);
						cout << endl << playerPointer[j].getName() << " calls " << trump;
						//escape the loop
						j = 4;
						myGame.setBidCall();
					}
				}

			}

			/*if it was not ordered up and not bid, then then round over, else, play*/
			if (myGame.getBidCallStatus() == false && myGame.getOrderUpStatus() == false) {
				cout << endl << "Round " << myGame.getGameRound() << " is over.  Everyone passed.";
			}
			/*play*/
			else {

				for (int j = 0; j < 4; j++) {
					playerPointer = playerArray[j].getNextPlayer();

					//player in position 2 needs to lead (dealer is position 1)
					if (playerPointer->isDealer() == true) {
						//pointer +1 above the dealer (2) leads
						cout << endl << playerPointer->getNextPlayer()->getName() << " should lead.";

						//set player 2 as lead the first round -- need to add code for first round
						playerPointer->getNextPlayer()->setLead(true);

					}
				}
				//it's the first round, need to lead a card

				int roundRemainder = roundConverter(myGame.getGameRound());

				//get the trump abbreviation
				string firstLetterTrump = myGame.getTrump();

				
				//create the legal moves
				//CHANGE LATER -- HAVE PLAYER 1 ASSUME THE LED SUIT IS TRUMP
				playerArray[roundRemainder].createLegalMoves("H", firstLetterTrump);
				//find and print the best move
				playerArray[roundRemainder].findBestMove();

			    //Set the card led by player 1
				myGame.setLead(playerArray[roundRemainder].getBestMove());
				myGame.whoIsWinning(myGame.getLead(),0);

				//get the first letter led
				string tempFirstLetterLed = myGame.getLead();
				tempFirstLetterLed = tempFirstLetterLed[1];

				
				//Everyone else play a card
				Player* tempPointer = dealerPointer->getNextPlayer();
				tempPointer = tempPointer->getNextPlayer();
				for (int i = 0; i < 3; i++) {
					tempPointer->createLegalMoves(tempFirstLetterLed, firstLetterTrump);
					cout << endl << "these are the legal moves for " << (*tempPointer).getName() << endl;
					(*tempPointer).printLegalMoves();
					(*tempPointer).findBestMove();
					myGame.whoIsWinning(tempPointer->getBestMove(), (i+1));
					tempPointer = (*tempPointer).getNextPlayer();
				}

				//score the round
				cout << endl << "The round scores are: ";
				int tempScore=-2;
				int tempScoreIndex = -1;
				for (int k = 0; k < 4; k++) {
					cout << endl << k << ":  " << myGame.getRoundScore(k);
					if (myGame.getRoundScore(k) > tempScore) {
						tempScore = myGame.getRoundScore(k);
						tempScoreIndex = k;
					}
				}
				cout << endl << "Index of the highest score is: " << tempScoreIndex << endl;
				cout << playerArray[tempScoreIndex].getName() << " won that round." << endl;

			}



			/************* Clear the flags for that round**************/
			//clear the dealer
			for (int j = 0; j < 4; j++) {
				playerArray[j].setDealerFalse();
				playerArray[j].setLead(false);
			}
			myGame.clearStatus();
			/************* ------------------------------**************/
			myGame.clearPlayedCards();

			if (testRoundCounter == testRoundLimit) {
				myGame.setGameOver();
			}
			++testRoundCounter;
	}
	return(0);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

//helper function begin

void printDealerHelper(Player helperPlayers[4]) {
	list <Player>::iterator it;
	for (int i = 0; i < 4; i++)
	{
		if (helperPlayers[i].isDealer() )
		{
			cout << endl << helperPlayers[i].getName() << " is the dealer.";
			return;
		}
	}
}

void dealCards(Player helperPlayers[4], Deck &helperDeck) {
	for (int i = 0; i < 4; i++)
	{
		helperPlayers[i].getCards(helperDeck);
	}
}

void handStr(Player helperPlayers[4], string fCard) {
	for (int i = 0; i < 4; i++)
	{
		helperPlayers[i].calcHandStrength(fCard);
	}
}

void printHelper(Player helperPlayers[4]) {
	for (int i = 0; i < 4; i++)
	{
			helperPlayers[i].printHand();
	}
}


bool dealerPickUp(Player &dealerPlayer) {
	if (dealerPlayer.getStrength() > 5)
	{
		dealerPlayer.setDealerPickup(true);
		return(true);
	}
	else
	{
		dealerPlayer.setDealerPickup(false);
		return(false);
	}
}

string suitAbbreviation(string theSuit) {
	if (theSuit == "D") { return("Diamonds"); }
	else if (theSuit == "H") {return("Hearts");}
	else if (theSuit == "C") { return("Clubs"); }
	else if (theSuit == "S") { return("Spades"); }
}

int roundConverter(const int& theRound) {
	int temp;
	temp = theRound % 4;
	if (temp == 0) {
		return(4);
	}
	else
	{
		return(temp);
	}
}

