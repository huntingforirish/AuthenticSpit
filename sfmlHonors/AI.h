//=================================
//forward declared dependencies
class Hand;
class PlayerDeck;
class GameDeck;
class Relationship;

#pragma once
#include "Hand.h"
#include "Relationship.h"
#include "PlayerDeck.h"
#include "GameDeck.h"
#include <SFML/Audio.hpp>

class AI
{
private:
	
	Hand &aIHand;
	Hand &oppHand;
	PlayerDeck &aIDeck;
	std::string aIDifficulty, aISkill;

	std::vector <CardRef> usableCards, oppUsableCards;

	std::vector <Relationship> relations, oppRelations;

	bool &playingStatus;

	GameDeck &gDeck1;
	GameDeck &gDeck2;	

	sf::SoundBuffer cardPlace3B;
	sf::SoundBuffer cardSlide1B;
	sf::SoundBuffer cardSlide3B;
	sf::Sound cardPlace3;
	sf::Sound cardSlide1;
	sf::Sound cardSlide3;

	bool cardPlayable;

	Relationship chosenRel;
	CardRef chosenCard = CardRef(0, "", 0);
	std::string chosenGDeck;

public:

	// get
	bool getCardPlayable() { return this->cardPlayable; }
	CardRef getChosenCard() { return this->chosenCard; }
	std::string getChosenGDeck() { return this->chosenGDeck; }

	//set
	void setDifficulty(std::string d) { this->aIDifficulty = d; }
	void setSkill(std::string s) { this->aISkill = s; }

	//constructor
	AI(Hand& hand, Hand& oppH, PlayerDeck& deck, GameDeck& gD1, GameDeck& gD2,
		std::string difficulty, std::string skill, bool &playing)
		: aIHand(hand), oppHand(oppH), aIDeck(deck), 
		gDeck1(gD1), gDeck2(gD2), playingStatus(playing)
		{

		this->aIDifficulty = difficulty;
		this->aISkill = skill;

		std::string path = "\../Resources/Sounds/";
		
		if (!this->cardPlace3B.loadFromFile(path + "cardPlace3.ogg")) {
			//display error
			std::cout << "Error Loading File: cardPlace3.ogg" << std::endl;
		}
		else {			
			this->cardPlace3.setBuffer(cardPlace3B);
			this->cardPlace3.setVolume(50);
		}
		
		if (!this->cardSlide1B.loadFromFile(path + "cardSlide1.ogg")) {
			//display error
			std::cout << "Error Loading File: cardSlide1.ogg" << std::endl;
		}
		else {
			this->cardSlide1.setBuffer(cardSlide1B);
			this->cardSlide1.setVolume(50);
		}

		
		if (!this->cardSlide3B.loadFromFile(path + "cardSlide3.ogg")) {
			//display error
			std::cout << "Error Loading File: cardSlide3.ogg" << std::endl;
		}
		else {
			this->cardSlide3.setBuffer(cardSlide3B);
			this->cardSlide3.setVolume(50);
		}


	}

	//destructor
	~AI();

	sf::SoundBuffer& getCardPlace3() { return this->cardPlace3B; }
	sf::SoundBuffer& getCardSlide3() { return this->cardSlide1B; }

	// function to represent a hand, controlling the playing of cards 
	void playHand();

	// a function to represent the other hand, controlling stockpiling and card flipping
	int otherHand();

	// returns whether any relationships are playable
	bool anyRelPlayable(std::vector <Relationship>);

	// returns whether any relationships are usable
	bool anyRelUsable(std::vector <Relationship>);

	// returns whether any card references are usable
	bool anyRefUsable(std::vector <CardRef>);

	// gathers vital game information and resets temporary values
	void initialise();

	// explores the AI's cards and searches for relationships
	void analyseCards();

	// explores the opponent's cards and searches for relationships
	void analyseOppCards();

	// adjusts the weight of relationships that are playable
	void adjPlayableW(int,int);

	// adjusts the weight of relationships that the opponent could play relationships on
	void adjOppRelPlayable();

	// adjusts the weight of relationships that the opponent could play individual cards on
	void adjOppCardPlayable();

	// adjusts the weight of cardRefs that the opponent could play relationships on
	void adjCardWeight(int i);

	// adds weight to relationships that lead towards others, and returns chosenRel
	void evaluateRels();

	// adds weight to playable cards that lead to others, and returns chosenCard
	void evaluateCard();

	//returns other usable relationships
	std::vector <Relationship> getUsableRels(int);

	//returns other usable Card References
	std::vector <CardRef> getUsableCards(int i);

	// compares relationship distance incrementally
	int calcDistInc(int, CardRef);

	// compares relationship distance decrementally
	int calcDistDec(int, CardRef);

	//calculates the minimum distance between the end of one relationship 
	//and the beginning of another
	int calcMinDistance(int, int, int, int);

	// recieves the minimum distance and uses it to add weight to a relation
	void calcMinWeight(int, int);

	//calculates the average distance and uses it to add weight
	void calcAvgWeight(int,int, int);

	// counts the weight of each game deck and returns the new value
	int countGDWeight(int);

	// decides which gameDeck the chosen card will be laid upon
	void selectGameDeck();

	//plays the chosen card on the desired gameDeck
	bool playCard();
};

