//included dependencies
#pragma once
#include "Deck.h"
class HandPile :
	public Deck
{
private:
	int id; // identifies which handpile it is
	bool selected = false; // identifies whether the hand is currently selected
public:
	//get functions
	int getID() { return this->id; }
	bool getSelected() { return this->selected; }

	//set function
	void setSelected(bool s) { this->selected = s; }

	//constructor
	HandPile(int i) : Deck() {
		this->id = i;
	}

	//destructor
	~HandPile();

	//returns all cards to the player's deck
	void dumpHand(Deck);

	//returns whether the top card may be stockpiled onto another HandPile
	bool isStockpilable(HandPile);

	//stockpiles a card
	bool stockpile(HandPile*);

	//returns whether every card in the pile is the same and visible
	bool isUnique();

	//returns the number of visible cards on the pile 
	int countUnique();

	//returns whether the top card may be placed onto a GamePile
	bool isPlayable(Deck);
};

