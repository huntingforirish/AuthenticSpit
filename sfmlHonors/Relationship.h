//=================================
//forward declared dependencies
class Card;

//=================================
//included dependencies
#pragma once
#include "CardRef.h"
#include <vector>
class Relationship
{
private:
	std::vector <CardRef> cards; //stores the related cards
	float weight; //stores the relationship's weight
	float similarity = 0; //stores the total similarity between this and the oppenent's cards
	bool playable = false; //defines whether the relationship can be played
	bool usable = true; //determines whether the relationship can be used without interfering with another
public:
	//constructor
	Relationship();

	//destructor
	~Relationship();

	//get functions
	std::vector <CardRef> getCards() { return this->cards; }
	float getWeight() { return this->weight; }
	float getSimilarity() { return this->similarity; }
	bool getPlayable() { return this->playable; }
	bool getUsable() { return this->usable; }

	//set functions
	void setWeight(float w) { this->weight = w; }
	void setSimilarity(float s) { this->similarity = s; }
	void setPlayable(bool p) { this->playable = p; }
	void setUsable(bool u) { this->usable = u; }

	//adds a card to the relationship
	void addCard(CardRef);

	//resets the relationship for finding alternative card combinations
	void resetCards();

	//adds a float to the weight value
	void addWeight(float);

	//subtracts a float from the weight value
	void subWeight(float);

	//adds a value to similarity
	void addSimilarity(float);
};

