//=================================
//included dependencies
#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Card
{
private:
	//class attribute declaration
	int index; //a number to determine the card's value
	std::string suit; //the card's suit
	std::string name; //the card's display name
	sf::Sprite sprite; //stores the card's sprite
	bool visible = false; //determines whether the card is face up

public:
	//get functions
	int getIndex() { return this->index; }
	std::string getSuit() { return this->suit; }
	std::string getName() { return this->name; } // defined later, determined by index
	sf::Sprite getSprite() { return this->sprite; }
	bool getVisible() { return this->visible; }


	//set functions
	void setIndex(int i) { index = i; }
	void setSuit(std::string s) { suit = s; }
	void setName(std::string n) { name = n; }
	void setVisible(bool v) { visible = v; }

	//constructor
	Card(int, std::string, sf::Sprite&);

	//overloaded constructor
	Card();

	//destructor
	~Card();

	//applies the appropriate name given the index
	void createName();

	//flips the card over
	void flip();

	//sets the card's sprite's position
	void setPosition(sf::Vector2f);

	//prints card details
	void toString();

}; // end class declaration