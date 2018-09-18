#include "stdafx.h"
#include "Relationship.h"


Relationship::Relationship()
{
}


Relationship::~Relationship()
{
}

//adds a card to the relationship
void Relationship::addCard(CardRef card) {
	this->cards.push_back(card);
	this->weight += 1;
}


//resets the relationship for finding alternatives
void Relationship::resetCards() {
	this->cards.clear();
	this->weight = 0;
}

//adds a float to the weight value
void Relationship::addWeight(float f) {
	this->weight = this->weight + f;
}

//subtracts a float from the weight value
void Relationship::subWeight(float f) {
	this->weight -= f;
}

//adds a value to similarity
void Relationship::addSimilarity(float f) {
	this->similarity += f;
}