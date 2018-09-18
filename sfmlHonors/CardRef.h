#pragma once
class CardRef
{
private:
	int index; // identifies the card's index
	std::string suit; // identifies the card's suit
	int handNumber; // identifies the hand in which the card came from
	bool usable = true; // variable used when AI is checking for additional cards
	float cardWeight = 1; // weight used when relationships aren't playable
public:
	//get functions
	int getIndex() { return this->index; }
	std::string getSuit() { return this->suit; }
	int getHandNo() { return this->handNumber; }
	bool getUsable() { return this->usable; }
	float getCardWeight() { return this->cardWeight; }

	//set function
	void setIndex(int i) { this->index = i; }
	void setUsable(bool u) { this->usable = u; }
	void setCardWeight(float w) { this->cardWeight = w; }

	//constructor
	CardRef(int, std::string, int);

	//destructor
	~CardRef();

	//determines whether a card is suitable for a relationship
	bool isRelated(int);

	//adds weight to the cardRef
	void addWeight(float);
};

