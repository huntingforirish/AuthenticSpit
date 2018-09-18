#include "stdafx.h"
#include "PlayerDeck.h"

//destructor
PlayerDeck::~PlayerDeck()
{
}

//deals cards before the start of a round
void PlayerDeck::dealHand(Deck* hand1, Deck *hand2, Deck*hand3, Deck *hand4, Deck *hand5) {

	this->shuffle();

	//loops to deal cards in an identical fashion to the original game
	for (int i = 0; i < 5; i++) {

		//these actions must only be performed once
		//on the first run
		if (i == 0 and this->size() > 1) {
			this->play(*hand1);
			this->place(*hand2);
		}
		else if (i == 0) {
			this->place(*hand2);
		}

		//on the second run
		if (i == 1 and this->size() > 0) {
			this->play(*hand2);
		}

		//the rest 
		if (i < 2 and this->size() > 0) {
			this->place(*hand3);
		}
		else if (i == 2 and this->size() > 0) {
			this->play(*hand3);
		}

		if (i < 3 and this->size() > 0) {
			this->place(*hand4);
		}
		else if (i == 3 and this->size() > 0) {
			this->play(*hand4);
		}

		if (i == 4 and this->size() > 0) {
			this->play(*hand5);
		}
		else if (this->size() > 0) {
			this->place(*hand5);
		}
	}//end 4* loop
}//end dealHand