#include "stdafx.h"
#include "CardRef.h"

//contructor
CardRef::CardRef(int i, std::string s, int h)
{
	this->index = i;
	this->suit = s;
	this->handNumber = h;
}

//destructor
CardRef::~CardRef()
{
}

//determines whether a card is suitable for a relationship
bool CardRef::isRelated(int cardIndex) {

	//if the top card index of gameDeck is 1 greater or less than the HandPile

	if ((this->index == (cardIndex - 1)) || (this->index == (cardIndex + 1))) {

		return true;
	}
	//if one card is an ace and the other is a king
	else if ((this->index == 13 and cardIndex == 1)
		|| (this->index == 1 and cardIndex == 13)) {

		return true;
	}
	//if either card is a joker
	else if (this->index == 14 || cardIndex == 14) {

		return true;
	}
	else {
		return false;
	}
}

//adds weight to the cardRef
void CardRef::addWeight(float w) {
	this->cardWeight = this->cardWeight + w;
}
