//included dependencies
#pragma once
#include "Deck.h"
#include <SFML/Graphics.hpp>
class StartDeck :
	public Deck
{
private:
	//class attribute declaration
	std::string cardStyle;
	sf::Texture spritesheet;
	sf::Texture &refSpritesheet = spritesheet;
public:
	//set functions
	void setSprites(sf::Texture &t) { this->refSpritesheet = t; }

	//constructor
	StartDeck(std::string);

	//destructor
	~StartDeck();

	//creates the deck of 52 unique cards
	void createDeck();

	//alternately deals all cards to each player's decks
	void deal(Deck&, Deck&);
};

