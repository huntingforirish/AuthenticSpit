#include "stdafx.h"
#include "Player.h"
#include <sstream>
#include <iostream>
#include <fstream>

Player::Player(int pos)
{
	this->position = pos;
}

Player::~Player()
{
}

//asks the user to input a name
void Player::setName() {
	std::string input;
	std::cout << "input player name: ";
	getline(std::cin, input);
	this->name = input;
}

void Player::toString() {
	std::cout << this->name << " is player " << std::to_string(this->position) << std::endl;
}