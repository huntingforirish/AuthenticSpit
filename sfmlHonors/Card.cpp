#include "stdafx.h"
#include "Card.h"
#include <sstream>
#include <iostream>

//constructor method
Card::Card(int index, std::string suit,sf::Sprite& tSprite)
{
	this->index = index;
	this->suit = suit;
	this->sprite = tSprite;
}

//overloaded method
Card::Card() {

}

//destructor method
Card::~Card()
{
}

//assigns a name to face cards
void Card::createName() {

	switch (this->index) {

	case 1:
		this->setName("Ace");
		break;
	case 11:
		this->setName("Jack");
		break;
	case 12:
		this->setName("Queen");
		break;
	case 13:
		this->setName("King");
		break;
	default:
		std::string tempName = std::to_string(this->index);
		this->setName(tempName);
	} //end switch
}//end createName

 //flips the card over
void Card::flip() {
	if (this->visible == true) {
		this->setVisible(false);
	}
	else {
		this->setVisible(true);
	}
}

//sets the card's sprite's position
void Card::setPosition(sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

//prints card details
void Card::toString() {
	if (this->visible == true) {
		std::cout << "The " << this->name << " of " << this->suit << std::endl;
	}
	else {
		std::cout << "A face down card" << std::endl;
	}
}