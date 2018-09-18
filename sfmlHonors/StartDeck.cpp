#include "stdafx.h"
#include "StartDeck.h"
#include <iostream>
#include <sstream>
#include <SFML/OpenGL.hpp>

//constructor
StartDeck::StartDeck(std::string style) : Deck() {
	this->cardStyle = style;
	std::string path;
	if (cardStyle == "Modern") {
		path = "\../Resources/Sprites/Cards/Spritesheets/Modern3.png";
	}
	else if (cardStyle == "Classic") {
		path = "\../Resources/Sprites/Cards/Spritesheets/Classic2.png";
	}

	if (!this->spritesheet.loadFromFile(path)) {
		//display error
		std::cout << "Error Loading File: " + cardStyle + ".png" << std::endl;
	}
	else {
		sf::Texture::bind(&this->spritesheet);
		this->spritesheet.setSmooth(true);
	}

}

StartDeck::~StartDeck()
{
}
//creates the deck of 52 unique cards
void StartDeck::createDeck() {

	//declaring spritesheet co-ordinate variables
	int x;
	int y;

	//loops for every suit
	for (int i = 0; i < 4; i++) {

		//determines the currently selected suit
		std::string suitArray[4] = { "Clubs","Diamonds","Hearts","Spades" };
		std::string suit = suitArray[i];

		//loops for every possible card index
		for (int j = 1; j <= 13; j++) {

			//determines x co-ordinate on spritesheet, dependant on index
			x = (j - 1) * 112;

			//determines y co-ordinate on spritesheet, dependant on suit
			switch (i) {
			case 0:
				y = 0;
				break;
			case 1:
				y = 156;
				break;
			case 2:
				y = 312;
				break;
			case 3:
				y = 468;
				break;
			}

			sf::Sprite cardSprite(this->refSpritesheet, sf::IntRect(x, y, 112, 156));

			//creates the card
			Card newCard = Card(j, suit, cardSprite);
			newCard.createName();

			//adds the newly created card to the deck
			std::vector <Card> temp = this->getFullDeck();
			temp.push_back(newCard);
			this->setFullDeck(temp);

		}//end 13* for loop
	}//end 4* for loop

	this->shuffle();
	std::cout << "Deck created" << std::endl;
}//end createDeck

 //alternately deals all cards to each player's decks
void StartDeck::deal(Deck &player1Deck, Deck &player2Deck) {

	//temporary variable to represent the number of card pairs
	int decksize = (this->getFullDeck().size() / 2);

	//loops for 26 times, once for each pair of cards dealt
	for (int i = 0; i < decksize; i++) {

		//deals a card to player 1
		this->place(player1Deck);

		//deals a card to player 2
		this->place(player2Deck);
	}
}