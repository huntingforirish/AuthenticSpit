//=================================
//included dependencies
#include "stdafx.h"
#include "Deck.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <functional>

//=================================
//constructor method
Deck::Deck()
{
}

//destructor method
Deck::~Deck()
{
}

//randomises the order of cards in the deck, shuffling it
void Deck::shuffle() {

	// creates an instance of an engine.
	std::random_device rnd_device;
	// specifies the engine and distribution.
	std::mt19937 my_engine(rnd_device());
	std::uniform_int_distribution<int> dist(1, this->size());

	//intially shuffles the deck
	std::shuffle(std::begin(this->fullDeck), std::end(this->fullDeck), my_engine);

	//reshuffles the deck to improve randomisation
	std::shuffle(std::begin(this->fullDeck), std::end(this->fullDeck), my_engine);

	//reshuffles the deck again to further improve randomisation
	std::shuffle(std::begin(this->fullDeck), std::end(this->fullDeck), my_engine);
}

//removes the top card from the deck
void Deck::pop() {

	// pops fulldeck
	this->fullDeck.pop_back();

}

//copies top card of fullDeck to another pile
void Deck::push(Deck &anyPile) {

	// pushes fullDeck
	std::vector <Card> temp = anyPile.getFullDeck();
	temp.push_back(this->fullDeck.back());
	anyPile.setFullDeck(temp);

}

//removes the top card and places it onto another pile
void Deck::place(Deck &anyPile) {

	push(anyPile);
	pop();

}

//places a card and flips it over
void Deck::play(Deck &anyPile) {

	this->fullDeck.back().flip();
	place(anyPile);

}

//returns the number of cards present in fullDeck
int Deck::size() {

	return this->fullDeck.size();

}

//if a deck is empty, returns true
bool Deck::isEmpty() {

	//returns empty if the size of fullDeck = 0
	if (fullDeck.size() == 0) {
		return 1;
	}
	else {
		return 0;
	}

}

//returns the top card
Card Deck::topCard() {

	return this->fullDeck.back();

}

//points to the top card
Card& Deck::refTopCard() {

	return this->fullDeck.back();

}

//sets the card's sprite's position
void Deck::setPosition(int item, sf::Vector2f pos) {
	this->fullDeck[item].setPosition(pos);
}


//deletes every card in the deck
void Deck::wipe() {
	this->fullDeck.clear();
}

//prints every card in the deck
void Deck::toString() {
	if (this->fullDeck.size() > 0) {
		for (unsigned int i = 0; i < this->fullDeck.size(); i++) {
			this->fullDeck[i].toString();
		}
	}
}