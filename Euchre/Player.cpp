#include "pch.h"
#include "Player.h"
#include <algorithm>
#include <string>

//Define the helper functions
double takeRankReturnStrength(string sentRank);
double countSideAceStrength(string sentRank);
int twoSuitsOrLess(bool oneVal, bool twoVal, bool threeVal, bool fourVal);
string bestBid(double d, double h, double s, double c);

/* Constructor*/
Player::Player(string myName, int pNumber, int theAggression)
{
	name = myName;
	playerNumber = pNumber;
	nextPlayer = NULL;
	aggression = theAggression;
	switch (pNumber)
	{
	case(1): position = 1; 
		break;
	case(2): position = 2;
		break;
	case(3): position = 3;
		break;
	case(4): position = 4;
		break;
	}
	//dealer = false;
}

/* Copy Constructor*/
Player::Player(const Player& obj) {
	name = obj.name;
	nextPlayer = NULL;
	//hand[5] = obj.hand[5];
}

void Player::setPosition(int myPosition) {
	position = myPosition;
	if (myPosition == 1) {
		dealer = true;
	}
	else{
		dealer = false;
	}
	if (myPosition == 3) {
		partnerDealer = true;
	}
	else {
		partnerDealer = false;
	}
}

void Player::removeWeakCard(string tCard) {
	double scores[5];
	double bestScore=-50;
	int bestIndex;
	/*need to set one card to "NULL" each time*/
	string tempHand[5];
	string saveHand[5];
	
	/*create some copies to save the original hand*/
	for (int j = 0; j < 5; j++) {
		saveHand[j] = hand[j];
	}

	for (int i = 0; i < 5; i++) {
		//set the ith card to NULL
		hand[i] = "NULL";
		//calculate hand strength
		calcHandStrength(tCard);
		//save the score
		scores[i] = handStrength;
		cout << endl << "scores " << scores[i];
		//reset the hand
		hand[i] = saveHand[i];
		//if this new hand is better than previous, save this index
		if (scores[i] > bestScore) { 
			bestScore = handStrength; 
			bestIndex = i;
		}
	}
	cout << endl << endl << name << " will remove the " << hand[bestIndex] << " card";
	hand[bestIndex] = tCard;
	cout << endl << name << " new hand is " << endl;
	printHand();
}

Player::~Player()
{
}

bool Player::isDealer() {
	return(dealer);
}

void Player::setDealerFalse() {
	dealer = false;
}

string Player::getName() {
	return(name);
}

void Player::getCards(Deck& shuffledDeck) {
	//player 2
	if (this->position == 2){
		hand[0] = shuffledDeck.cards[7];
		hand[1] = shuffledDeck.cards[8];
		hand[2] = shuffledDeck.cards[9];
		hand[3] = shuffledDeck.cards[18];
		hand[4] = shuffledDeck.cards[19];
	}
	//player 3
	if (this->position == 3) {
		hand[0] = shuffledDeck.cards[2];
		hand[1] = shuffledDeck.cards[3];
		hand[2] = shuffledDeck.cards[4];
		hand[3] = shuffledDeck.cards[13];
		hand[4] = shuffledDeck.cards[14];
	}
	//player 4
	if (this->position == 4) {
		hand[0] = shuffledDeck.cards[5];
		hand[1] = shuffledDeck.cards[6];
		hand[2] = shuffledDeck.cards[15];
		hand[3] = shuffledDeck.cards[16];
		hand[4] = shuffledDeck.cards[17];
	}
	if (this->position == 1) {
		hand[0] = shuffledDeck.cards[0];
		hand[1] = shuffledDeck.cards[1];
		hand[2] = shuffledDeck.cards[10];
		hand[3] = shuffledDeck.cards[11];
		hand[4] = shuffledDeck.cards[12];
	} 

	if (this->dealer == true) {
		//turnCard = shuffledDeck.cards[20];
		kitty[0] = shuffledDeck.cards[21];
		kitty[1] = shuffledDeck.cards[22];
		kitty[2] = shuffledDeck.cards[23];
	}

}

void Player::printHand() {
	cout << endl << name << "'s " << "Hand:";
	for (int i = 0; i < 5; i++) {
		cout << endl << hand[i];
	}
	cout << endl;
}

void Player::bid() {
	bestBidStrength = 0;
	double diamonds;
	double hearts;
	double spades;
	double clubs;
	string best;
	calcHandStrength("XD");
	diamonds = handStrength;
	calcHandStrength("XH");
	hearts = handStrength;
	calcHandStrength("XS");
	spades = handStrength;
	calcHandStrength("XC");
	clubs = handStrength;
	bestBidSuit = bestBid(diamonds, hearts, spades, clubs);
	if (bestBidSuit == "D") { bestBidStrength = diamonds; }
	else if (bestBidSuit == "H") { bestBidStrength = hearts; }
	else if (bestBidSuit == "S") { bestBidStrength = spades; }
	else if (bestBidSuit == "C") { bestBidStrength = clubs; }

	cout << endl << name << " best bid suit is:  " << bestBidSuit;
	cout << endl << " and best bid strength is:  " << bestBidStrength << endl;
}

void Player::calcHandStrength(string flippedCard) 
{
	string flippedCardRank= flippedCard.substr(0, 1);
	string flippedCardSuit = flippedCard.substr(1, 1);
	string rank, suit;
	handStrength = 0;
	bool hasHearts=0;
	bool hasDiamonds=0;
	bool hasSpades=0;
	bool hasClubs=0;
	bool singleSuit=0;
	bool twoSuited=0;
	int numSuits=0;
	bool hasLeft=0;
	bool hasRight=0;
	bool jackUp=0;

	//for each card in the hand
	for (int i = 0; i < 5; i++) {
		rank = hand[i].substr(0, 1);
		suit = hand[i].substr(1, 1);
		
		//if the flipped car matches the suit
		if (flippedCardSuit == suit) {
			//call helper function to determine matching suits
			handStrength += takeRankReturnStrength(rank);
		}
		else {
			//flipped card does not match the suit, but count the side aces
			handStrength += countSideAceStrength(rank);
		}

		//check for left
		if (flippedCardSuit == "D") {
			if (rank == "J" && suit == "H") { 
				handStrength += 5;
				hasLeft = true;
			}
		}
		if (flippedCardSuit == "H") {
			if (rank == "J" && suit == "D") { 
				handStrength += 5; 
				hasLeft = true;
			}
		}
		if (flippedCardSuit == "C") {
			if (rank == "J" && suit == "S") { 
				handStrength += 5; 
				hasLeft = true;
			}
		}
		if (flippedCardSuit == "S") {
			if (rank == "J" && suit == "C") { 
				handStrength += 5;
				hasLeft = true;
			}
		}

		//calculate singleSuit and twoSuited
		if (suit == "D") { hasDiamonds = 1; }
		else if (suit == "H") { hasHearts = 1; }
		else if (suit == "C") { hasClubs = 1; }
		else if (suit == "S") { hasSpades = 1; }
		numSuits = twoSuitsOrLess(hasDiamonds, hasHearts, hasClubs, hasSpades);
		if (numSuits == 1) { (singleSuit = 1); }
		else if (numSuits == 2) { (twoSuited = 1); }
	}

	//if the top card is a jack
	if (flippedCard == "J")
	{
		jackUp = true;
	}

//if dealer/partner, will we be adding that card to their hand?
double goodOrBadCard = 0;
goodOrBadCard = takeRankReturnStrength(flippedCardRank);
if (dealer == true || partnerDealer == true)
{
	handStrength += (goodOrBadCard / 2);
}
//gotta order up to the enemy
else {
	handStrength -= goodOrBadCard;
}

//cout << endl << "Hand Strength for " << this->name << " is: " << this->handStrength;
}

void Player::setNextPosition() {
	switch (position) {
	case 1:  position = 4;
		break;
	case 2:  position = 1;
		break;
	case 3:  position = 2;
		break;
	case 4:  position = 3;
		break;
	}
}

double Player::getStrength() {
	return(handStrength);
}

void Player::setOrderUp(bool oU) {
	orderUp = oU;
}

void Player::setDealerPickup(bool dP) {
	dealer = dP;
}

void Player::setNextPlayer(Player& nP) {
	this->nextPlayer = &nP;
}

Player* Player::getNextPlayer() {
	return(nextPlayer);
}

int Player::getPosition() {
	return(position);
}

void Player::setDealer() {
	this->dealer = true;
}

bool Player::orderUpFunction() {
	if (aggression < handStrength) {
		orderUp = true;
	}
	else
	{
		orderUp = false;
	}
	return(orderUp);
}


int Player::getBestBidStrength() {
	return(bestBidStrength);
}

string Player::getBestBidSuit() {
	return(bestBidSuit);
}

int Player::getAggression() {
	return(aggression);
}

string Player::playCard(string trumpCard) {
	
	//You Called It


	//You didn't call It
	
	
	this->printLegalMoves();
	
	
	return("Card");
}

void Player::createLegalMoves(string theLedSuit, string theTrump) {
	//set legal moves to NULL
	for (int i = 0; i < 5; i++) {
		legalMoves[i] = "NULL";
	}

	//Do you lead?  If so, throw whatever
	if (isLead == true) {
		for (int i = 0; i < 5; i++)
		{
			legalMoves[i] = hand[i];
		}
	}
	//You don't lead, you follow suit
	else {
		string tempString = "";
		string tempSuit = "";
		string tempRank = "";
		for (int i = 0; i < 5; i++)
		{
			tempString = hand[i];
			tempSuit = tempString[1];
			tempRank = tempString[0];
			
			if (tempSuit == theLedSuit) 
			{
				if (!((theLedSuit == "D" && tempString == "JD" && theTrump == "H") ||
					(theLedSuit == "H" && tempString == "JH" && theTrump == "D") ||
					(theLedSuit == "C" && tempString == "JC" && theTrump == "S") ||
					(theLedSuit == "S" && tempString == "JS" && theTrump == "C"))) {
					//if you have the led suit, then you have to add that suit as a legal move, unless it is the left
					legalMoves[i] = hand[i];
				}
			}

			// check for the left as a legal move
			if (theLedSuit == "D" && tempString == "JH" && theTrump == "D") {
				legalMoves[i] = hand[i];
			}
			else if (theLedSuit == "H" && tempString == "JD"  && theTrump == "H") {
				legalMoves[i] = hand[i];
			}
			else if (theLedSuit == "C" && tempString == "JS" && theTrump == "C") {
				legalMoves[i] = hand[i];
			}
			else if (theLedSuit == "S" && tempString == "JC" && theTrump == "S") {
				legalMoves[i] = hand[i];
			}

		}
	}
}

void Player::printLegalMoves() {
	for (int i = 0; i < 5; i++)
	{
		cout << legalMoves[i] << endl;
	}
}


void Player::setLead(bool theLead) {
	isLead = theLead;
}

void Player::findBestMove() {
	bool hasTrump = false;
	for (int i = 0; i < 5; i++) {
		if (legalMoves[i] != "NULL") {
			hasTrump = true;
			bestMove = legalMoves[i];
		}
	}
	
	if (hasTrump == false) {
		cout << endl << name << " has no trump... can play whatever (will play first card): " << endl;
		//set temporary best move
		bestMove = hand[0];
		cout << bestMove;
	}
	else {
		cout << endl << "The best move is " << bestMove << endl;
	}
}

string Player::getBestMove() {
	return(bestMove);
}



/*helper function to help determine hand strength
Input:  Rank (string)
Output:  Strength (double)
*/
double takeRankReturnStrength(string sentRank) {
	if (sentRank == "N") {
		return(2);
	}
	else if (sentRank == "T") {
		return(2.5);
	}
	else if (sentRank == "J") {
		return(6);
	}
	else if (sentRank == "Q") {
		return(3);
	}
	else if (sentRank == "K") {
		return(3.5);
	}
	else if (sentRank == "A") {
		return(4);
	}
	else
	{
		return(0);
	}
}

double countSideAceStrength(string sentRank) {
	if (sentRank == "A") {
		return(1.5);
	}
	else if(sentRank == "K")
	{
		return(.4);
	}
	else if (sentRank == "Q")
	{
		return(.3);
	}
	else if (sentRank == "J")
	{
		return(.2);
	}
	else if (sentRank == "T")
	{
		return(.1);
	}
	else { return(0); }
}

int twoSuitsOrLess(bool oneVal, bool twoVal, bool threeVal, bool fourVal) {
	return(oneVal + twoVal + threeVal + fourVal);
}

string bestBid(double d, double h, double s, double c) {
	double cards[4] = { d,h,s,c };
	const int N = sizeof(cards) / sizeof(double);
	int myIndex;


	myIndex = std::distance(cards, max_element(cards, cards + N));


	if (myIndex == 0) { return("D"); }

	else if (myIndex == 1) { return("H"); }
	else if (myIndex == 2) { return("S"); }
	else if (myIndex == 3) { return("C"); }


}