#include "stdafx.h"
#include "Game.h"

//THIS CLASS IS OBSOLETE
//NO LONGER USED 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Game::Game(Player p1, Player p2) {
	this->player1 = p1;
	this->player2 = p2;
}


Game::~Game()
{
}

//sets the game up in preparation
void Game::setup() {

	//creates and prints the initial deck
	this->newDeck.createDeck();
	this->newDeck.toString();

	//deals the deck's contents out to either player
	this->newDeck.deal(this->player1Deck, this->player2Deck);

	std::cout << "Player 1's deck contents post deal" << std::endl;

	this->player1Deck.toString();

	std::cout << "Player 2's deck contents post deal" << std::endl;

	this->player2Deck.toString();

	//deals each
	this->player1Deck.dealHand(&this->player1Hand.getHand1(), &this->player1Hand.getHand2(), &this->player1Hand.getHand3(), &this->player1Hand.getHand4(), &this->player1Hand.getHand5());
	this->player2Deck.dealHand(&this->player2Hand.getHand1(), &this->player2Hand.getHand2(), &this->player2Hand.getHand3(), &this->player2Hand.getHand4(), &this->player2Hand.getHand5());

	std::cout << "Player 1's deck size post dealing their hand" << std::endl;
	std::cout << this->player1Deck.size() << std::endl;
	std::cout << "Player 2's deck size post dealing their hand" << std::endl;
	std::cout << this->player2Deck.size() << std::endl;

	std::cout << "" << std::endl;

	this->player1Hand.getHand1().toString();
	this->player1Hand.getHand2().toString();
	this->player1Hand.getHand3().toString();
	this->player1Hand.getHand4().toString();
	this->player1Hand.getHand5().toString();

	std::cout << "" << std::endl;

	this->player2Hand.getHand1().toString();
	this->player2Hand.getHand2().toString();
	this->player2Hand.getHand3().toString();
	this->player2Hand.getHand4().toString();
	this->player2Hand.getHand5().toString();

	std::cout << "" << std::endl;
}

//begins the round by flipping over cards onto the game piles
void Game::startRound() {

	this->player1Deck.play(this->gameDeck1);
	this->player2Deck.play(this->gameDeck2);

	gameDeck1.toString();
	gameDeck2.toString();

	std::cout << "" << std::endl;

	std::cout << player1Hand.getHand1().isPlayable(gameDeck1) << std::endl;
	std::cout << player1Hand.getHand1().isPlayable(gameDeck2) << std::endl;
	std::cout << player1Hand.getHand2().isPlayable(gameDeck1) << std::endl;
	std::cout << player1Hand.getHand2().isPlayable(gameDeck2) << std::endl;
	std::cout << player1Hand.getHand3().isPlayable(gameDeck1) << std::endl;
	std::cout << player1Hand.getHand3().isPlayable(gameDeck2) << std::endl;
	std::cout << player1Hand.getHand4().isPlayable(gameDeck1) << std::endl;
	std::cout << player1Hand.getHand4().isPlayable(gameDeck2) << std::endl;
	std::cout << player1Hand.getHand5().isPlayable(gameDeck1) << std::endl;
	std::cout << player1Hand.getHand5().isPlayable(gameDeck2) << std::endl;

	std::cout << "" << std::endl;

	std::cout << player2Hand.getHand1().isPlayable(gameDeck1) << std::endl;
	std::cout << player2Hand.getHand1().isPlayable(gameDeck2) << std::endl;
	std::cout << player2Hand.getHand2().isPlayable(gameDeck1) << std::endl;
	std::cout << player2Hand.getHand2().isPlayable(gameDeck2) << std::endl;
	std::cout << player2Hand.getHand3().isPlayable(gameDeck1) << std::endl;
	std::cout << player2Hand.getHand3().isPlayable(gameDeck2) << std::endl;
	std::cout << player2Hand.getHand4().isPlayable(gameDeck1) << std::endl;
	std::cout << player2Hand.getHand4().isPlayable(gameDeck2) << std::endl;
	std::cout << player2Hand.getHand5().isPlayable(gameDeck1) << std::endl;
	std::cout << player2Hand.getHand5().isPlayable(gameDeck2) << std::endl;

	this->playingStatus = true;
}



//clears all decks and resets game values
void Game::wipe() {
	this->player1Deck.wipe();
	this->player2Deck.wipe();
	this->gameDeck1.wipe();
	this->gameDeck2.wipe();
	this->player1Hand.wipe();
	this->player1Hand.wipe();
}