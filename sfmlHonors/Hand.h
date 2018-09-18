//=================================
//forward declared dependencies
class HandPile;
class Player;

//included depend
#pragma once
#include "HandPile.h"
#include "Player.h"
#include "CardRef.h"

class Hand
{
private:
	//class attribute declaration
	HandPile hand1 = HandPile(1); //the player's first hand pile
	HandPile hand2 = HandPile(2); //the player's second hand pile
	HandPile hand3 = HandPile(3); //the player's third hand pile
	HandPile hand4 = HandPile(4); //the player's fourth hand pile
	HandPile hand5 = HandPile(5); //the player's final hand pile
	HandPile noSelection = HandPile(0); //handpile returned when no pile is selected
	int position; //the position of player that owns the hand


public:

	//get functions
	HandPile getHand1() { return this->hand1; }
	HandPile getHand2() { return this->hand2; }
	HandPile getHand3() { return this->hand3; }
	HandPile getHand4() { return this->hand4; }
	HandPile getHand5() { return this->hand5; }
	int getPosition() { return this->position; }

	//set function
	void setPosition(int p) { this->position = p; }

	//constructor
	Hand(int);

	//destructor
	~Hand();

	//returns the corresponding handpile
	HandPile getHandPile(int);

	//validates the chosenCard before playing it
	bool validateHand(int, int);

	//function places a card from a specified hand onto a deck
	void placeHand(int, Deck&);

	// unused functions, kept for reference
	//function to place a card from hand1 onto a deck
	void placeHand1(Deck&);

	//stockpiles a card from hand1 onto another handpile
	void stockpileHand1(HandPile*);

	//returns true if a hand is empty
	bool anyHandEmpty();

	//returns true if every card in the player's hand is face up
	bool allCardsVisible();

	//returns true if every card in the player's hand is face up
	bool allTopCardsVisible();

	//flips the top card of hand1
	void hand1FlipTopC();

	//flips the top card of hand2
	void hand2FlipTopC();

	//flips the top card of hand3
	void hand3FlipTopC();

	//flips the top card of hand4
	void hand4FlipTopC();

	//flips the top card of hand5
	void hand5FlipTopC();

	//returns the currently selected hand
	HandPile* getHandSelected();

	//sets hand 1 as the selected pile
	void setHand1Selected();

	//sets hand 2 as the selected pile
	void setHand2Selected();

	//sets hand 3 as the selected pile
	void setHand3Selected();

	//sets hand 4 as the selected pile
	void setHand4Selected();

	//sets hand 5 as the selected pile
	void setHand5Selected();

	//counts the total number of cards in the hand
	int countCards();

	//determines whether a player can play any cards
	bool canPlay(Deck,Deck);

	//decides which card may be stockpiled and does so
	bool aIStockpile();

	//returns usable card indexes and locations for processing by AI
	std::vector <CardRef> getUsableCards();

	//checks if a hand is empty
	bool handEmpty(int);

	//clears any cards left after a round, returning them to their deck
	void clearHand(Deck*);

	//deletes all cards from all hand piles
	void wipe();
};