//=================================
//forward declared dependencies
class HandPile;

//=================================
//included dependencies
#pragma once
#include "Deck.h"
#include "HandPile.h"

class PlayerDeck :
	public Deck
{
private:
	//Player owner; //the player that owns the deck
public:

	//constructor
	PlayerDeck() : Deck() {}

	//destructor
	~PlayerDeck();

	//deals cards before the start of a round
	void dealHand(Deck*, Deck*, Deck*, Deck*, Deck*);


};