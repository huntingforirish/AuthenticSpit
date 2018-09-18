#include "stdafx.h"
#include "GameDeck.h"

//destructor
GameDeck::~GameDeck()
{
}

//returns all cards to the player's deck
void GameDeck::dumpDeck(Deck& playerDeck) {

	//stores the initial size of the deck
	int size = this->size();

	//loops for every item in the deck
	for (int i = 0; i < size; i++) {

		//places the top card face down onto the player's deck
		if (this->size() > 0) {
			this->play(playerDeck);
		}
		else {
			std::cout << "Error: GameDeck attempted to play cards when it no longer could" << std::endl;
		}
		

	}//end size* loop
}//end dumpHand

 //returns a gameDeck's topCard's index, if there is one
int GameDeck::topIndex() {
	if (this->size() > 0) {
		return this->topCard().getIndex();
	}
	return 100;
}