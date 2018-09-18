#pragma once
#include "Deck.h"
class GameDeck :
	public Deck
{
public:
	//contructor
	GameDeck() : Deck() {};

	//destructor
	~GameDeck();

	//returns all cards to the player's deck
	void dumpDeck(Deck&);

	//returns a gameDeck's topCard's index, if there is one
	int topIndex();
};