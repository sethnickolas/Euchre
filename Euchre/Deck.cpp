#include "pch.h"
#include "Deck.h"
//#include "time.h"

Deck::Deck()
{
	string rank[6] = { "N","T","J","Q","K","A" };
	string suits[4] = { "S","C","H","D" };
	int count = 0;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 6; j++) {
			
			cards[count] = rank[j] + suits[i];
			count++;
			
		}

	}
}

Deck::~Deck()
{
}


/*take two random numbers between 0 and NUMCARDS and shuffle the array 
location for each of the cards
*/
void Deck::shuffleCards()
{
	srand(time(NULL));  //initialize random number seed
	for (int i = 0; i < NUMCARDS; i++) {
		int rand1, rand2;
		string tempCard;
		rand1 = rand() % NUMCARDS; // rand1 in the range 0 to NUMCARDS
		rand2 = rand() % NUMCARDS; // rand2 in the range 0 to NUMCARDS
		tempCard = cards[rand1]; //store card1 value
		cards[rand1] = cards[rand2]; //overwrite card1 value
		cards[rand2] = tempCard; //store the temp card in card2
	}
}

void Deck::printDeck()
{
	for (int i = 0; i < NUMCARDS; i++){
		if (i == 0) {
			cout << endl << "CARD LIST" << endl;
		}
		cout << cards[i] << endl;
	}
}

void Deck::setTurnCard() 
{
	turnCard = cards[20];
}

string Deck::getTurnCard()
{
	return(turnCard);
}

void Deck::printTurnCard()
{
	cout << endl << "The turn card is " << turnCard;
}