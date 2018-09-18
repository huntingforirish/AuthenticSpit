#pragma once
#include "Player.h"
#include "StartDeck.h"
#include "PlayerDeck.h"
#include "Hand.h"
#include "HandPile.h"
#include "GameDeck.h"

//THIS CLASS IS OBSOLETE
//NO LONGER USED 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Game
{
private:
	//class attribute declaration
	Player player1;
	Player player2;
	StartDeck newDeck = StartDeck("Modern");
	PlayerDeck player1Deck = PlayerDeck();
	PlayerDeck player2Deck = PlayerDeck();
	GameDeck gameDeck1 = GameDeck();
	GameDeck gameDeck2 = GameDeck();
	Hand player1Hand = Hand(this->player1.getPosition());
	Hand player2Hand = Hand(this->player2.getPosition());
	bool playingStatus = false;

public:
	//get functions
	Player getPlayer1() { return this->player1; }
	Player getPlayer2() { return this->player2; }
	PlayerDeck getP1Deck() { return this->player1Deck; }
	PlayerDeck getP2Deck() { return this->player2Deck; }
	GameDeck getGDeck1() { return this->gameDeck1; }
	GameDeck getGDeck2() { return this->gameDeck2; }
	Hand getP1Hand() { return this->player1Hand; }
	Hand getP2Hand() { return this->player2Hand; }
	bool getPlayStatus() { return this->playingStatus; }

	//set functions
	void setPlayStatus(bool p) { this->playingStatus = p; }

	Game(Player, Player);
	~Game();

	//sets the game up in preparation
	void setup();

	//begins the round by flipping over cards onto the game piles
	void startRound();

	//clears all decks and resets game values
	void wipe();
};