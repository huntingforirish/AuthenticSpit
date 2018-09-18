#include "stdafx.h"
#include "AI.h"


AI::~AI()
{
}

// function to represent a hand, controlling the playing of cards 
void AI::playHand() {

	if (playingStatus == true) {
		if (aIHand.canPlay(gDeck1, gDeck2)) {
			this->initialise();
			this->analyseCards();
			
			// can only see the players cards when they have more than 5 / AI Skill barrier
			if (oppHand.countCards() > 5 and aISkill != "Rookie" and aISkill != "Intermediate") {
				this->analyseOppCards();
			}			

			// adds weight to playable relationships and marks them as such
			if (gDeck1.size() > 0 and gDeck2.size() > 0) {
				this->adjPlayableW(gDeck1.topCard().getIndex(), gDeck2.topCard().getIndex());
			}
			else if (gDeck1.size() > 0) {
				this->adjPlayableW(gDeck1.topCard().getIndex(), 100);
			}
			else {
				this->adjPlayableW(100, gDeck2.topCard().getIndex());
			}

			// if a relationship can be played
			if (anyRelPlayable(relations)) {
				std::cout << "AI can play a relation" << std::endl;

				//if the opponent has relationships / AI Skill barrier
				if (oppRelations.size() > 0 and
					(aISkill == "Veteran" || aISkill == "Master")) {

					// adjusts the weight of relationships that the opponent could play relationships on
					this->adjOppRelPlayable();		
				}
				
				// can only use the players cards when they have more than 5 / AI Skill barrier
				if (oppHand.countCards() > 5 and aISkill == "Master") {
					// adjusts the weight of relationships that the opponent could play individual cards on
					this->adjOppCardPlayable();
				}				

				// adds weight to relationships that lead towards others 
				// and selects the relationship with the highest weight
				this->evaluateRels();

				// sets chosenCard to the first card in chosenRel
				this->chosenCard = chosenRel.getCards().front();


			}// end if AI can play a relationship
			else {
				std::cout << "AI can play but not a relation" << std::endl;

				// adds weight to playable cards that lead to others, and returns chosenCard
				this->evaluateCard();
			}

			// plays chosenCard onto a pile, aiming to incovenince the opponent
			// and improve the AI's own situation
			this->selectGameDeck();
		}// end if AI can play		
		
	}// end if playing
}

// a function to represent the other hand, controlling stockpiling and card flipping
int AI::otherHand() {

	if (aIHand.aIStockpile()) {

		std::cout << "A card was stockpiled successfully" << std::endl;

		this->cardSlide3.play();

		return 10;

	}
	else if (!aIHand.allTopCardsVisible()) {
		std::cout << "aI can flip a card" << std::endl;

		if (aIHand.getHand1().size() > 0) {
			if (!aIHand.getHand1().topCard().getVisible()) {
				aIHand.hand1FlipTopC();
				if (aIHand.countCards() > 5) {
					this->cardPlace3.play();
				}				
				return 1;
			}
		}
			
		if (aIHand.getHand2().size() > 0) {
			if (!aIHand.getHand2().topCard().getVisible()) {
				aIHand.hand2FlipTopC();
				if (aIHand.countCards() > 5) {
					this->cardPlace3.play();
				}
				return 2;
			}
		}

		if (aIHand.getHand3().size() > 0) {
			if (!aIHand.getHand3().topCard().getVisible()) {
				aIHand.hand3FlipTopC();
				if (aIHand.countCards() > 5) {
					this->cardPlace3.play();
				}
				return 3;
			}
		}

		if (aIHand.getHand4().size() > 0) {
			if (!aIHand.getHand4().topCard().getVisible()) {
				aIHand.hand4FlipTopC();
				if (aIHand.countCards() > 5) {
					this->cardPlace3.play();
				}
				return 4;
			}
		}

		if (aIHand.getHand5().size() > 0) {
			if (!aIHand.getHand5().topCard().getVisible()) {
				aIHand.hand5FlipTopC();
				if (aIHand.countCards() > 5) {
					this->cardPlace3.play();
				}
				return 5;
			}
		}
	}
	else {
		std::cout << "aI cannot make any moves" << std::endl;
		return 0;
	}

}

//returns whether any relationships are playable
bool AI::anyRelPlayable(std::vector <Relationship> rels) {
	for (int unsigned i = 0; i < rels.size(); i++) {
		if (rels[i].getPlayable()) {
			this->cardPlayable = true;
			return true;
		}
	}
	return false;
}

//returns whether any relationships are usable
bool AI::anyRelUsable(std::vector <Relationship> rels) {
	for (int unsigned i = 0; i < rels.size(); i++) {
		if (rels[i].getUsable()) {
			return true;
		}
	}
	return false;
}

//returns whether any card references are usable
bool AI::anyRefUsable(std::vector <CardRef> refs) {
	for (int unsigned i = 0; i < refs.size(); i++) {
		if (refs[i].getUsable()) {
			return true;
		}
	}
	return false;
}


//gathers vital game information and resets temporary values
void AI::initialise() {
	this->usableCards = this->aIHand.getUsableCards();
	this->oppUsableCards = oppHand.getUsableCards();
	this->relations.clear();
	this->oppRelations.clear();
	this->cardPlayable = false;
	this->chosenCard.setCardWeight(0.0f);
	this->chosenRel.setWeight(0.0f);
	this->chosenGDeck = "";
}

// adjusts the weight of relationships that are playable
void AI::adjPlayableW(int gD1, int gD2) {
	
	for (int unsigned i = 0; i < this->relations.size(); i++) {
		if (this->relations[i].getCards().front().isRelated(gD1)
			|| this->relations[i].getCards().front().isRelated(gD2)) {
			float f = this->relations[i].getWeight();
			f *= 2;
			this->relations[i].setWeight(f);
			this->relations[i].setPlayable(true);
		}
	}
	
	if (aISkill != "Rookie" and aISkill != "Intermediate") {
		for (int unsigned i = 0; i < this->oppRelations.size(); i++) {
			if (this->oppRelations[i].getCards().front().isRelated(gD1)
				|| this->oppRelations[i].getCards().front().isRelated(gD2)) {
				float f = this->oppRelations[i].getWeight();
				f *= 2;
				this->oppRelations[i].setWeight(f);
				this->oppRelations[i].setPlayable(true);
			}
		}
	}
	
}

// adjusts the weight of relationships that the opponent could play relationships on
void AI::adjOppRelPlayable() {
	
	// for every relationship
	for (int unsigned i = 0; i < relations.size(); i++) {
		for (int unsigned j = 0; j < oppRelations.size(); j++) {

			// for every card in both relationships
			for (int unsigned k = 0; k < relations[i].getCards().size(); k++) {
				for (int unsigned l = 0; l < oppRelations[j].getCards().size(); l++) {

					if (relations[i].getCards()[k].isRelated(oppRelations[j].getCards()[l].getIndex())) {

						if (oppRelations[j].getPlayable()) {
							this->relations[i].addSimilarity(0.3f);
						}
						else {
							this->relations[i].addSimilarity(0.2f);
						}
					}

				}
			}

		}
		// adjusts the similarity of the relationship
		if (relations[i].getSimilarity() > 0) {

			float f = relations[i].getSimilarity();
			f /= oppRelations.size();
			relations[i].setSimilarity(f);
			if (aISkill == "Veteran") {
				relations[i].subWeight(relations[i].getSimilarity());
			}
		}
	}
}

// adjusts the weight of relationships that the opponent could play individual cards on
void AI::adjOppCardPlayable() {

	// for every relationship
	for (int unsigned i = 0; i < relations.size(); i++) {
		// for every card in the AI relationships
		for (int unsigned j = 0; j < relations[i].getCards().size(); j++) {
			// for every usable card the opponent has
			for (int unsigned k = 0; k < oppUsableCards.size(); k++) {

				if (relations[i].getCards()[j].isRelated(oppUsableCards[k].getIndex())) {
					relations[i].addSimilarity(0.1f);
				}

			}

		}
		// adjusts the similarity and weight of the relationship
		if (relations[i].getSimilarity() > 0) {

			relations[i].subWeight(relations[i].getSimilarity());
		}
	}

}
// adjusts the weight of cardRefs that the opponent could play relationships on
void AI::adjCardWeight(int i) {
	
	// for every relationship the opponent has
	for (int unsigned j = 0; j < oppRelations.size(); j++) {

		// for every card in this relationship
		for (int unsigned l = 0; l < oppRelations[j].getCards().size(); l++) {

			if (usableCards[i].isRelated(oppRelations[j].getCards()[l].getIndex())) {

				if (oppRelations[j].getPlayable()) {
					this->usableCards[i].addWeight(0.3f);
				}
				else {
					this->usableCards[i].addWeight(0.2f);
				}
			}

		}
			

	}
	// adjusts the weight of the cardRef
	if (usableCards[i].getCardWeight() > 1) {

		float f = usableCards[i].getCardWeight();
		f -= 1;
		f /= oppRelations.size();
		this->usableCards[i].setCardWeight(1 - f);
	}
	
}

// adds weight to relationships that lead towards others, and returns chosenRel
void AI::evaluateRels() {

	for (int unsigned i = 0; i < relations.size(); i++) {

		int min = 100;
		std::vector <Relationship> tempList = this->getUsableRels(i);

		// AI Skill barrier
		if (aISkill != "Rookie") {

			// if any other relationship can be used in conjunction with [i]
			if (anyRelUsable(tempList)) {
				// add weight to relationships that lead towards others

				// returns the lowest distance
				for (int unsigned j = 0; j < relations.size(); j++) {

					if (i != j and tempList[j].getUsable()) {
						min = this->calcMinDistance(tempList[j].getCards().front().getIndex(), min, i, j);
					}
				}// end for j
			}// end if anyRelUsable
			 // otherwise
			else {
				// adds weight to relationships that lead to other cards being played

				if (aISkill != "Intermediate") {

					std::vector <CardRef> tempUsableCards = this->getUsableCards(i);

					if (anyRefUsable(tempUsableCards)) {

						// returns the lowest distance
						for (int unsigned j = 0; j < tempUsableCards.size(); j++) {

							if (tempUsableCards[j].getUsable()) {
								min = this->calcMinDistance(tempUsableCards[j].getIndex(), min, i, j);
							}
						}// end for j				
					}
				}
				
			}

			// uses the lowest distance to add weight to the relationship
			this->calcMinWeight(min, i);

		}		

		// compares Relationship weights and sets chosenRel to the highest
		if (relations[i].getWeight() > chosenRel.getWeight()
			and relations[i].getPlayable()) {
			this->chosenRel = relations[i];
		}
	}

}

// adds weight to playable cards that lead to others, and returns chosenCard
void AI::evaluateCard() {

	//identifies playable cards
	for (int unsigned i = 0; i < usableCards.size(); i++) {

		if (usableCards[i].isRelated(gDeck1.topIndex())
			|| usableCards[i].isRelated(gDeck2.topIndex())) {
			
			this->cardPlayable = "true";

			// AI Skill barrier
			if (aISkill == "Veteran" || aISkill == "Master") {
				//adjusts the weight of individual cards if they are related to relations the opponent can play
				this->adjCardWeight(i);
			}			

			// AI Skill barrier
			if (aISkill == "Master") {
				int total = 0;

				for (int unsigned j = 0; j < usableCards.size(); j++) {

					if (i != j) {

						int counter1 = 0;
						int counter2 = 0;

						// compares relationship distance incrementally
						counter1 = this->calcDistInc(usableCards[j].getIndex(), usableCards[i]);

						// compares relationship distance decrementally
						counter2 = this->calcDistDec(usableCards[j].getIndex(), usableCards[i]);

						// finds the smallest distance and adds it to total
						if (counter1 < counter2 and counter2 != 0) {
							total = total + counter1;
						}
						else {
							total = total + counter2;
						}
					}// end if i!= j
				}// end for j

				 //calculates the average distance and uses it to add weight
				this->calcAvgWeight(total, usableCards.size(), i);
			}			

			// compares CardRef weights and sets chosenCard to the highest valued CardRef
			if (usableCards[i].getCardWeight() > chosenCard.getCardWeight()) {
				this->chosenCard = usableCards[i];
			}
		}// end if card is playable
	}// end for i
}

//returns other usable relationships
std::vector <Relationship> AI::getUsableRels(int i) {

	std::vector <Relationship> tempList = this->relations;

	//for every relationship
	for (int unsigned a = 0; a < relations.size(); a++) {

		//for every card in the relationship
		for (int unsigned b = 0; b < relations[i].getCards().size(); b++) {

			//for every card in the current relationship 
			for (int unsigned c = 0; c < relations[a].getCards().size(); c++) {
				if (relations[i].getCards()[b].getIndex() == relations[a].getCards()[c].getIndex()
					and relations[i].getCards()[b].getSuit() == relations[a].getCards()[c].getSuit()) {
					tempList[a].setUsable(false);
				}
			}
		}

	}
	return tempList;
}

//returns other usable Card References
std::vector <CardRef> AI::getUsableCards(int i) {

	std::vector <CardRef> tempUsableCards = aIHand.getUsableCards();

	//for every card in the relationship
	for (int unsigned a = 0; a < relations[i].getCards().size(); a++) {

		//for every relationship
		for (int unsigned b = 0; b < tempUsableCards.size(); b++) {

			if (relations[i].getCards()[a].getIndex() == tempUsableCards[b].getIndex()
				and relations[i].getCards()[a].getSuit() == tempUsableCards[b].getSuit()) {
				tempUsableCards[b].setUsable(false);
			}
		}
	}
	return tempUsableCards;
}

// compares relationship distance incrementally
int AI::calcDistInc(int tempIndex, CardRef card) {
	int counter = 0;
	int adjustedIndex = 0;
	for (int k = 1; card.isRelated(adjustedIndex); k++) {

		adjustedIndex = tempIndex + k;

		if (adjustedIndex == 14) {
			tempIndex = 1;
			k = 0;
		}
		counter++;

	}
	return counter;
}

// compares relationship distance decrementally
int AI::calcDistDec(int tempIndex, CardRef card) {
	int counter = 0;
	int adjustedIndex = 0;
	for (int k = 1; card.isRelated(adjustedIndex); k++) {

		adjustedIndex = tempIndex - k;

		if (adjustedIndex == 14) {
			tempIndex = 1;
			k = 0;
		}
		counter++;

	}
	return counter;
}

//calculates the minimum distance between the end of one relationship 
//and the beginning of another
int AI::calcMinDistance(int cardIndex, int min, int i, int j) {

	int counter = 0;
	int adjustedIndex = 0;

	// compares relationship distance incrementally
	counter = this->calcDistInc(cardIndex, this->relations[i].getCards().back());

	if (min > counter and counter != 0) {
		min = counter;
	}

	counter = 0;
	
	// compares relationship distance incrementally
	counter = this->calcDistDec(cardIndex, this->relations[i].getCards().back());

	if (min > counter and counter != 0) {
		min = counter;
	}

	return min;
}

// recieves the minimum distance and uses it to add weight to a relation
void AI::calcMinWeight(int min, int i) {
	if (min != 100) {
		float temp = 1;
		temp /= min;
		this->relations[i].addWeight(temp);
	}
}

//calculates the average distance and uses it to add weight
void AI::calcAvgWeight(int total, int uCardsSize, int i) {
	if (total > 0) {
		float avg = 0.0;
		float temp = 1.0;
		avg = (float)(total) / (float)(uCardsSize - 1.0);
		temp /= avg;
		usableCards[i].addWeight(temp);
	}
}

// counts the weight of each game deck and returns the new value
int AI::countGDWeight(int weight) {
	for (int unsigned j = 0; j < oppUsableCards.size(); j++) {

		if (oppUsableCards[j].isRelated(chosenCard.getIndex())) {
			weight = weight + 1;
		}
		else {
			weight = weight + 5;
		}
	}
	return weight;
}

// ~~ decides which gameDeck the chosen card will be laid upon ~~
void AI::selectGameDeck() {

	// if chosenCard can be played onto either pile
	if (chosenCard.isRelated(gDeck1.topIndex())
		and chosenCard.isRelated(gDeck2.topIndex())) {

		//values to store
		int gD1Weight = 0;
		int gD2Weight = 0;

		if (gDeck1.topIndex() != gDeck2.topIndex()
			and aISkill != "Rookie") {

			for (int unsigned i = 0; i < oppUsableCards.size(); i++) {

				if (oppUsableCards[i].isRelated(gDeck1.topIndex())
					and !oppUsableCards[i].isRelated(gDeck2.topIndex())) {
					gD1Weight = countGDWeight(gD1Weight);
				}
				else if (!oppUsableCards[i].isRelated(gDeck1.topIndex())
					and oppUsableCards[i].isRelated(gDeck2.topIndex())) {
					gD2Weight = countGDWeight(gD2Weight);
				}
			}
		}
		
		//selects the largest deck to play on, should both gamepiles have equal weight
		if (gD1Weight = gD2Weight) {
			if (gDeck1.size() >= gDeck2.size()) {
				
				this->chosenGDeck = "GameDeck1";
			}
			else {
				
				this->chosenGDeck = "GameDeck2";
			}
		}
		else if (gD1Weight > gD2Weight) {
			
			this->chosenGDeck = "GameDeck1";
		}
		else {
			
			this->chosenGDeck = "GameDeck2";
		}

	}
	// if chosenCard can be played on gameDeck1
	else if (chosenCard.isRelated(gDeck1.topIndex())) {
		std::cout << "AI played on gameDeck1" << std::endl;

		
		this->chosenGDeck = "GameDeck1";

	}
	// if chosenCard can be played on gameDeck2
	else if (chosenCard.isRelated(gDeck2.topIndex())) {
		std::cout << "AI played on gameDeck2" << std::endl;

		
		this->chosenGDeck = "GameDeck2";

	}
	else {
		std::cout << "Error: AI attempted to make an impossible move" << std::endl;
	}
}

//plays the chosen card on the desired gameDeck
bool AI::playCard() {
	if (chosenGDeck == "GameDeck1" and cardPlayable
		and !aIHand.handEmpty(chosenCard.getHandNo())) {
		if (chosenCard.isRelated(gDeck1.topCard().getIndex())
			and aIHand.validateHand(chosenCard.getIndex(),chosenCard.getHandNo())) {
			this->aIHand.placeHand(chosenCard.getHandNo(), gDeck1);
			this->cardSlide1.play();
			return true;
		}		
	}
	else if (chosenGDeck == "GameDeck2" and cardPlayable
		and !aIHand.handEmpty(chosenCard.getHandNo())) {
		if (chosenCard.isRelated(gDeck2.topCard().getIndex())
			and aIHand.validateHand(chosenCard.getIndex(), chosenCard.getHandNo())) {
			this->aIHand.placeHand(chosenCard.getHandNo(), gDeck2);
			this->cardSlide1.play();
			return true;
		}
	}
	return false;
}


// explores the AI's cards and searches for relationships
void AI::analyseCards() {

	relations.clear();

	// AI -- Card Analysis ~~ Identifies up to 8 cards in a relationship
	for (int unsigned i = 0; i < usableCards.size(); i++) {

		for (int unsigned j = 0; j < usableCards.size(); j++) { // checks for a 2 card relationship
			if (usableCards[i].isRelated(usableCards[j].getIndex())
				and relations.size() < 60) {

				Relationship genRelation = Relationship();
				genRelation.addCard(usableCards[i]);
				genRelation.addCard(usableCards[j]);

				for (int unsigned k = 0; k < usableCards.size(); k++) { // checks for a 3 card relationship
					if (usableCards[j].isRelated(usableCards[k].getIndex())
						and (k != i and k != j)
						and relations.size() < 50) {

						genRelation.resetCards();
						genRelation.addCard(usableCards[i]);
						genRelation.addCard(usableCards[j]);
						genRelation.addCard(usableCards[k]);

						for (int unsigned l = 0; l < usableCards.size(); l++) { // checks for a 4 card relationship
							if (usableCards[k].isRelated(usableCards[l].getIndex())
								and (l != i and l != j and l != k)
								and relations.size() < 40
								and aISkill != "Rookie"){

								genRelation.resetCards();
								genRelation.addCard(usableCards[i]);
								genRelation.addCard(usableCards[j]);
								genRelation.addCard(usableCards[k]);
								genRelation.addCard(usableCards[l]);

								for (int unsigned m = 0; m < usableCards.size(); m++) { // checks for a 5 card relationship
									if (usableCards[l].isRelated(usableCards[m].getIndex())
										and (m != i and m != j and m != k and m != l)
										and relations.size() < 30
										and aISkill != "Intermediate") {

										genRelation.resetCards();
										genRelation.addCard(usableCards[i]);
										genRelation.addCard(usableCards[j]);
										genRelation.addCard(usableCards[k]);
										genRelation.addCard(usableCards[l]);
										genRelation.addCard(usableCards[m]);

									}// end if l related to m
									if (m + 1 == usableCards.size()
										and (genRelation.getWeight() == 4
											|| genRelation.getWeight() == 5)) {
										this->relations.push_back(genRelation);
									}
								}// end for m

							}// end if k related to l
							if (l + 1 == usableCards.size()
								and genRelation.getWeight() == 3) {
								this->relations.push_back(genRelation);
							}
						}// end for l

					}// end if j related to k
					if (k + 1 == usableCards.size()
						and genRelation.getWeight() == 2) {
						this->relations.push_back(genRelation);
					}
				}// end for k

			}// end if i related to j
		}// end for j

	}// end for i

}

// explores the opponent's cards and searches for relationships
void AI::analyseOppCards() {

	// AI -- Card Analysis ~~ Identifies up to 6 cards in an opponent's Relationship
	for (int unsigned i = 0; i < oppUsableCards.size(); i++) {

		for (int unsigned j = 0; j < oppUsableCards.size(); j++) { // checks for a 2 card oppRelationship
			if (oppUsableCards[i].isRelated(oppUsableCards[j].getIndex())
				and relations.size() < 30) {

				Relationship genRelation = Relationship();
				genRelation.addCard(oppUsableCards[i]);
				genRelation.addCard(oppUsableCards[j]);

				for (int unsigned k = 0; k < oppUsableCards.size(); k++) { // checks for a 3 card oppRelationship
					if (oppUsableCards[j].isRelated(oppUsableCards[k].getIndex())
						and (k != i and k != j)
						and relations.size() < 25) {

						genRelation.resetCards();
						genRelation.addCard(oppUsableCards[i]);
						genRelation.addCard(oppUsableCards[j]);
						genRelation.addCard(oppUsableCards[k]);

						for (int unsigned l = 0; l < oppUsableCards.size(); l++) { // checks for a 4 card oppRelationship
							if (oppUsableCards[k].isRelated(oppUsableCards[l].getIndex())
								and (l != i and l != j and l != k)
								and relations.size() < 20 
								and aISkill != "Veteran") {

								genRelation.resetCards();
								genRelation.addCard(oppUsableCards[i]);
								genRelation.addCard(oppUsableCards[j]);
								genRelation.addCard(oppUsableCards[k]);
								genRelation.addCard(oppUsableCards[l]);

								for (int unsigned m = 0; m < oppUsableCards.size(); m++) { // checks for a 5 card oppRelationship
									if (oppUsableCards[l].isRelated(oppUsableCards[m].getIndex())
										and (m != i and m != j and m != k and m != l)
										and relations.size() < 15) {

										genRelation.resetCards();
										genRelation.addCard(oppUsableCards[i]);
										genRelation.addCard(oppUsableCards[j]);
										genRelation.addCard(oppUsableCards[k]);
										genRelation.addCard(oppUsableCards[l]);
										genRelation.addCard(oppUsableCards[m]);

									}// end if l related to m
									if (m + 1 == oppUsableCards.size()
										and (genRelation.getWeight() == 4
											|| genRelation.getWeight() == 5)) {
										this->oppRelations.push_back(genRelation);
									}
								}// end for m

							}// end if k related to l
							if (l + 1 == oppUsableCards.size()
								and genRelation.getWeight() == 3) {
								this->oppRelations.push_back(genRelation);
							}
						}// end for l

					}// end if j related to k
					if (k + 1 == oppUsableCards.size()
						and genRelation.getWeight() == 2) {
						this->oppRelations.push_back(genRelation);
					}
				}// end for k

			}// end if i related to j
		}// end for j

	}// end for i

}

