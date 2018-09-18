#include "stdafx.h"
#include "HandPile.h"

//destructor
HandPile::~HandPile()
{
}

//returns all cards to the player's deck
void HandPile::dumpHand(Deck playerDeck) {

	//stores the initial size of the deck
	int size = this->size();

	//loops for every item in the hand pile
	for (int i = 0; i < size; i++) {

		//places the card face-down onto the deck
		if (this->getFullDeck().back().getVisible() == true) {
			this->play(playerDeck);
		}
		else {
			this->place(playerDeck);
		}

	}//end size* loop
}//end dumpHand

 //returns whether the top card may be stockpiled onto another HandPile
bool HandPile::isStockpilable(HandPile pile) {

	//ensures that a visible card is in the handpile
	if (this->size() > 0) {

		if (this->topCard().getVisible() == true) {

			//
			if (pile.size() == 0) {
				if (this->isUnique() == false) {
					return true;
				}
			}
			else {
				//applies the rules for stockpiling
				if (this->topCard().getIndex() == pile.topCard().getIndex() and pile.topCard().getVisible() == true) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//stockpiles a card
bool HandPile::stockpile(HandPile* h) {
	if (this->isStockpilable(*h) == true) {
		this->place(*h);
		return true;
	}
	return false;
}


//returns whether every card in the pile is the same and visible
bool HandPile::isUnique() {
	if (!this->size() == 0) {
		for (int i = 0; i < this->size(); i++) {
			if ((this->getFullDeck()[i].getIndex() != this->topCard().getIndex())
				|| this->getFullDeck()[i].getVisible() == false) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	
	return true;
}

//returns the number of visible cards on the pile 
int HandPile::countUnique() {
	int counter = 0;
	for (int i = 0; i < this->size(); i++) {
		if (this->getFullDeck()[i].getVisible()) {
			counter++;
		}
	}
	return counter;
}

//returns whether the top card may be placed onto a GamePile
bool HandPile::isPlayable(Deck gameDeck) {

	if (this->size() > 0 and gameDeck.size() > 0) {

		if (this->topCard().getVisible() == true) {

			//if the top card index of gameDeck is 1 greater or less than the HandPile topCard
			if ((this->topCard().getIndex() == (gameDeck.topCard().getIndex() - 1))
				|| (this->topCard().getIndex() == (gameDeck.topCard().getIndex() + 1))) {

				return true;
			}
			//if one card is an ace and the other is a king
			else if ((this->topCard().getIndex() == 13 and gameDeck.topCard().getIndex() == 1)
				|| (this->topCard().getIndex() == 1 and gameDeck.topCard().getIndex() == 13)) {

				return true;
			}
			//if either card is a joker
			else if (this->topCard().getIndex() == 14 || gameDeck.topCard().getIndex() == 14) {

				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		
	}
	else {
		return false;
	}

}
