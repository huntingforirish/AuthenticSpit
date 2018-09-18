#pragma once
#include <string>
class Player
{
private:
	std::string name; //identifies the player
	int position; //determines which side the player is on
public:
	//get functions
	std::string getName() { return this->name; }
	int getPosition() { return this->position; }

	//set functions
	void setName();
	void setPosition(int i) { this->position = i; }


	Player() {}
	Player(int);
	~Player();

	//prints player details
	void toString();
};