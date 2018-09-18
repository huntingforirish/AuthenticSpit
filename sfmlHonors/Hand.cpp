#include "stdafx.h"
#include "Hand.h"
#include <sstream>


Hand::Hand(int p) {
	this->position = p;
}

Hand::~Hand()
{

}

HandPile Hand::getHandPile(int no) {
	switch (no) {
	case 1:
		return this->hand1;
		break;
	case 2:
		return this->hand2;
		break;
	case 3:
		return this->hand3;
		break;
	case 4:
		return this->hand4;
		break;
	case 5:
		return this->hand5;
		break;
	}
}

//counts the total number of cards in the hand
int Hand::countCards() {
	int total;
	total = this->getHand1().size() + this->getHand2().size() + this->getHand3().size()
		+ this->getHand4().size() + this->getHand5().size();
	return total;
}

//validates the chosenCard before playing it
bool Hand::validateHand(int chosenIndex, int chosenHand) {
	switch (chosenHand) {
	case 1: if (chosenIndex == hand1.topCard().getIndex()) {
		return true;
	}
		break;
	case 2: if (chosenIndex == hand2.topCard().getIndex()) {
		return true;
	}
		break;
	case 3: if (chosenIndex == hand3.topCard().getIndex()) {
		return true;
	}
		break;
	case 4: if (chosenIndex == hand4.topCard().getIndex()) {
		return true;
	}
		break;
	case 5: if (chosenIndex == hand5.topCard().getIndex()) {
		return true;
	}
		break;
	default:
		break;
	}
}

//function places a card from a specified hand onto a deck
void Hand::placeHand(int handNumber, Deck& gameDeck) {
	switch (handNumber) {
	case 1: this->hand1.place(gameDeck);
		break;
	case 2: this->hand2.place(gameDeck);
		break;
	case 3: this->hand3.place(gameDeck);
		break;
	case 4: this->hand4.place(gameDeck);
		break;
	case 5: this->hand5.place(gameDeck);
		break;
	default:
		break;
	}
}

// unused functions, kept for reference
//function to place a card from hand1 onto a deck
void Hand::placeHand1(Deck& gDeck) {
	this->hand1.place(gDeck);
}

//stockpiles a card from hand1 onto another handpile
void Hand::stockpileHand1(HandPile *reciever) {
	if (this->hand1.isStockpilable(*reciever) == true) {
		this->hand1.place(*reciever);
	}
}

//returns true if a hand is empty
bool Hand::anyHandEmpty() {
	if (this->hand1.size() == 0
		|| this->hand2.size() == 0
		|| this->hand3.size() == 0
		|| this->hand4.size() == 0
		|| this->hand5.size() == 0) {
		return true;
	}
	return false;
}

//returns true if every card in the player's hand is face up
bool Hand::allCardsVisible() {

	std::vector<HandPile> piles;
	piles.push_back(hand1);
	piles.push_back(hand2);
	piles.push_back(hand3);
	piles.push_back(hand4);
	piles.push_back(hand5);

	for (int unsigned i = 0; i < piles.size(); i++) {
		for (int j = 0; j < piles[i].size(); j++) {
			if (!piles[i].getFullDeck()[j].getVisible()) {
				return false;
			}
		}
	}

	return true;

}

//returns true if every top card in the player's hand is face up
bool Hand::allTopCardsVisible() {
	if (!anyHandEmpty()) {
		if ((this->hand1.topCard().getVisible()
			and this->hand2.topCard().getVisible()
			and this->hand3.topCard().getVisible()
			and this->hand4.topCard().getVisible()
			and this->hand5.topCard().getVisible()) == true) {

			return true;

		}
	}
	return false;
}


//flips the top card of hand1
void Hand::hand1FlipTopC() {
	this->hand1.refTopCard().flip();
}

//flips the top card of hand1
void Hand::hand2FlipTopC() {
	this->hand2.refTopCard().flip();
}

//flips the top card of hand3
void Hand::hand3FlipTopC() {
	this->hand3.refTopCard().flip();
}

//flips the top card of hand4
void Hand::hand4FlipTopC() {
	this->hand4.refTopCard().flip();
}

//flips the top card of hand5
void Hand::hand5FlipTopC() {
	this->hand5.refTopCard().flip();
}


//returns the currently selected hand
HandPile* Hand::getHandSelected() {

	if (this->hand1.getSelected() == true) {
		return &this->hand1;
	} 
	else if (this->hand2.getSelected() == true) {
		return &this->hand2;
	}
	else if (this->hand3.getSelected() == true) {
		return &this->hand3;
	}
	else if (this->hand4.getSelected() == true) {
		return &this->hand4;
	}
	else if (this->hand5.getSelected() == true) {
		return &this->hand5;
	}
	else {
		return &this->noSelection;
	}
}// end getHandSelected function

//sets hand 1 as the selected pile
void Hand::setHand1Selected() {
	this->hand1.setSelected(true);
}

//sets hand 2 as the selected pile
void Hand::setHand2Selected() {
	this->hand2.setSelected(true);
}

//sets hand 3 as the selected pile
void Hand::setHand3Selected() {
	this->hand3.setSelected(true);
}

//sets hand 4 as the selected pile
void Hand::setHand4Selected() {
	this->hand4.setSelected(true);
}

//sets hand 5 as the selected pile
void Hand::setHand5Selected() {
	this->hand5.setSelected(true);
}

//determines whether a player can play any cards
bool Hand::canPlay(Deck gamePile1, Deck gamePile2) {
	if ((this->hand1.isPlayable(gamePile1) + this->hand1.isPlayable(gamePile2) +
		this->hand2.isPlayable(gamePile1) + this->hand2.isPlayable(gamePile2) +
		this->hand3.isPlayable(gamePile1) + this->hand3.isPlayable(gamePile2) +
		this->hand4.isPlayable(gamePile1) + this->hand4.isPlayable(gamePile2) +
		this->hand5.isPlayable(gamePile1) + this->hand5.isPlayable(gamePile2)) == false) {
		//std::cout << "Player " + std::to_string(this->position) + " cannot play cards" << std::endl;
		return false;
	}
	else {
		return true;
	}
	
}

//decides which card may be stockpiled and does so
bool Hand::aIStockpile() {
	std::vector<HandPile> piles;
	piles.push_back(this->hand1);
	piles.push_back(this->hand2);
	piles.push_back(this->hand3);
	piles.push_back(this->hand4);
	piles.push_back(this->hand5);	

	for (int unsigned i = 0; i < 5; i++) {
		for (int unsigned j = 0; j < 5; j++) {
			if (piles[i].isStockpilable(piles[j])
				and ((piles[i].size() >= piles[j].size()
						and piles[i].countUnique() <= piles[j].countUnique())
					|| (!piles[i].isUnique() and (piles[j].isUnique()
						|| piles[j].size() == 0))
					|| (piles[i].countUnique() < piles[j].countUnique()
						and piles[j].isUnique()))
				and i != j) {

				int h = i + 1;

				switch (j) {
				case 0:
					this->placeHand(h,this->hand1);
					break;
				case 1:
					this->placeHand(h, this->hand2);
					break;
				case 2:
					this->placeHand(h, this->hand3);
					break;
				case 3:
					this->placeHand(h, this->hand4);
					break;
				case 4:
					this->placeHand(h, this->hand5);
					break;
				}
				
				return true;
			}
		}
	}

	return false;
	
}



//returns usable card indexes and locations for processing by AI
std::vector <CardRef> Hand::getUsableCards() {
	std::vector <CardRef> cards;

	for (int i = 0; i < this->hand1.size(); i++) {
		if (hand1.getFullDeck()[i].getVisible() == true) {
			CardRef card(hand1.getFullDeck()[i].getIndex(), hand1.getFullDeck()[i].getSuit(),1);
			cards.push_back(card);
		}
	}

	for (int i = 0; i < this->hand2.size(); i++) {
		if (hand2.getFullDeck()[i].getVisible() == true) {
			CardRef card(hand2.getFullDeck()[i].getIndex(), hand2.getFullDeck()[i].getSuit(), 2);
			cards.push_back(card);
		}
	}

	for (int i = 0; i < this->hand3.size(); i++) {
		if (hand3.getFullDeck()[i].getVisible() == true) {
			CardRef card(hand3.getFullDeck()[i].getIndex(), hand3.getFullDeck()[i].getSuit(), 3);
			cards.push_back(card);
		}
	}

	for (int i = 0; i < this->hand4.size(); i++) {
		if (hand4.getFullDeck()[i].getVisible() == true) {
			CardRef card(hand4.getFullDeck()[i].getIndex(), hand4.getFullDeck()[i].getSuit(), 4);
			cards.push_back(card);
		}
	}

	for (int i = 0; i < this->hand5.size(); i++) {
		if (hand5.getFullDeck()[i].getVisible() == true) {
			CardRef card(hand5.getFullDeck()[i].getIndex(), hand5.getFullDeck()[i].getSuit(), 5);
			cards.push_back(card);
		}
	}

	return cards;

}

//checks if a hand is empty
bool Hand::handEmpty(int i) {
	switch (i) {
	case 1:
		if (this->hand1.size() == 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		if (this->hand2.size() == 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 3:
		if (this->hand3.size() == 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 4:
		if (this->hand4.size() == 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 5:
		if (this->hand5.size() == 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}

//clears any cards left after a round, returning them to their deck
void Hand::clearHand(Deck *pDeck) {
	//empties hand 
	this->hand1.dumpHand(*pDeck);
	this->hand2.dumpHand(*pDeck);
	this->hand3.dumpHand(*pDeck);
	this->hand4.dumpHand(*pDeck);
	this->hand5.dumpHand(*pDeck);
}

//deletes all cards from all hand piles
void Hand::wipe(){
	this->hand1.wipe();
	this->hand2.wipe();
	this->hand3.wipe();
	this->hand4.wipe();
	this->hand5.wipe();
}