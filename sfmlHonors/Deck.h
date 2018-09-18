//=================================
//forward declared dependencies
class Card;

//=================================
//included dependencies
#pragma once
#include "Card.h"
#include <vector>

//=================================
//class Deck
class Deck
{
private:
	//class attribute declaration
	std::vector <Card> fullDeck; //stores
	std::vector <Card> &refFullDeck = fullDeck;
public:
	//get function
	
	std::vector <Card> getFullDeck() { return this->refFullDeck; }

	//set function
	void setFullDeck(std::vector <Card> v) { this->refFullDeck = v; }

	//contructor
	Deck();

	//destructor
	~Deck();

	//shuffles the deck
	void shuffle();

	//removes the top card from the deck
	void pop();

	//copies top card of fulldeck to another pile
	void push(Deck&);

	//removes the top card and places it onto another pile
	void place(Deck&);

	//places a card and flips it over
	void play(Deck&);

	//displays the number of cards present in fullDeck
	int size();

	//checks whether the deck is empty
	bool isEmpty();

	//returns the top card
	Card topCard();

	//points to the top card
	Card& refTopCard();

	//sets the card's sprite's position
	void setPosition(int, sf::Vector2f);

	//deletes every card in the deck
	void wipe();

	//prints out every item from the deck
	void toString();
};