//=================================
//included dependencies
#include "stdafx.h"
#include "Player.h"
#include "StartDeck.h"
#include "HandPile.h"
#include "AI.h"
#include <random>
#include <thread>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

// ================================
//forward declared dependencies

//=================================
// function definition

// function to draw any of the player's handpiles
void drawPlayerHand(Hand *playerHand, sf::RenderWindow * window, sf::Sprite &cardBack, int handNo, int x, int y) {
	for (int i = 0; i < playerHand->getHandPile(handNo).size(); i++) {

		//does not display the top card whilst the pile is selected
		if (playerHand->getHandPile(handNo).getSelected() == true and (i + 1) == playerHand->getHandPile(handNo).size()) {
			//do nothing
		}
		else {

			//temporary variable to represent the current card
			Card tempCard = playerHand->getHandPile(handNo).getFullDeck()[i];

			// displays the card face if it's visible
			if (tempCard.getVisible() == true) {

				//sets the card's position, placing it 2 pixels below the last card
				tempCard.setPosition(sf::Vector2f((float)x, (float)(y + (2 * i))));

				//creates and draws the sprite
				window->draw(tempCard.getSprite());
			}
			else {
				// draws the card back instead of its face
				cardBack.setPosition((float)x, (float)(y + (2 * i)));
				window->draw(cardBack);
			}

		}

	}// end for loop
}

// function to draw any of the opponent's handpiles
void drawOpponentHand(Hand *playerHand, sf::RenderWindow * window, sf::Sprite &cardBack, int handNo, int x, int y) {
	for (int i = 0; i < playerHand->getHandPile(handNo).size(); i++) {
		
		//temporary variable to represent the current card
		Card tempCard = playerHand->getHandPile(handNo).getFullDeck()[i];

		// displays the card face if it's visible
		if (tempCard.getVisible() == true and playerHand->countCards() > 5) {

			//sets the card's position, placing it 2 pixels below the last card
			tempCard.setPosition(sf::Vector2f((float)x, (float)(y + (2 * i))));

			//creates and draws the sprite
			window->draw(tempCard.getSprite());
		}
		else {
			// draws the card back instead of its face
			cardBack.setPosition((float)x, (float)(y + (2 * i)));
			window->draw(cardBack);
		}		

	}// end for loop
}

//changes the current app State
void changeMenu(std::string& appState, std::string newState) {
	appState = newState;
}

// generates a random number between two values to represent it's reaction speed
// for playing cards, dependant on the AI's difficulty
sf::Time calcAIPlaySpeed(std::string s) {

	// creates an instance of an engine.
	std::random_device rnd_device;
	// specifies the engine and distribution.
	std::mt19937 my_engine(rnd_device());

	int min = 0;
	int max = 0;

	if (s == "Easy") {
		min = 1000;
		max = 2000;
	}
	else if (s == "Medium") {
		min = 650;
		max = 1700;
	}
	else if (s == "Hard") {
		min = 400;
		max = 1200;
	}

	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
	auto random_integer = uni(rnd_device);

	return sf::milliseconds(random_integer);
}

// generates a random number between two values to represent it's reaction speed
// for other interactions, dependant on the AI's difficulty
sf::Time calcAIOtherSpeed(std::string s) {

	// creates an instance of an engine.
	std::random_device rnd_device;
	// specifies the engine and distribution.
	std::mt19937 my_engine(rnd_device());

	int min = 0;
	int max = 0;

	if (s == "Easy") {
		min = 900;
		max = 1600;
	}
	else if (s == "Medium") {
		min = 600;
		max = 1200;
	}
	else if (s == "Hard") {
		min = 350;
		max = 900;
	}

	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
	auto random_integer = uni(rnd_device);

	return sf::milliseconds(random_integer);
}

int main()
{
	//=================================
	// game variable declaration
	Player player1 = Player(1);
	Player player2 = Player(2);
	StartDeck newDeck = StartDeck("Modern");
	PlayerDeck player1Deck = PlayerDeck();
	PlayerDeck player2Deck = PlayerDeck();
	GameDeck gameDeck1 = GameDeck();
	GameDeck gameDeck2 = GameDeck();
	Hand player1Hand = Hand(player1.getPosition());
	Hand player2Hand = Hand(player2.getPosition());

	// variables to represent application states

	std::string appState = "MainMenu";
	std::string gameState = "Pre-Round";
	std::string condition;
	bool playingStatus = false;

	//end round display text variables
	bool displayResult = false;
	sf::Sprite result;
	int a = 255;

	HandPile* p1Hand1 = &player1Hand.getHand1();
	

	// AI variable declaration
	std::string aIDifficulty = "Easy";
	std::string aISkill = "Intermediate";
	sf::Time aIPlayReaction = calcAIPlaySpeed(aIDifficulty);
	sf::Time aIOtherReaction = calcAIOtherSpeed(aIDifficulty);
	std::thread playHand;
	std::thread otherHand;

	AI gameAI = AI(player2Hand, player1Hand, player2Deck, gameDeck1,
		gameDeck2, aIDifficulty, aISkill,playingStatus);


	// temporary variable declaration for drawing cards
	sf::Sprite s;
	Card tempCard(0, "", s);


	//=================================
	// font creation
	std::string path;
	path = "\../Resources/Fonts/";

	sf::Font carved;
	if (!carved.loadFromFile(path + "PWChalk.ttf")) {
		// display error
		std::cout << "Error Loading File: PWChalk.ttf" << std::endl;
	}

	//=================================
	// texture creation
	path = "\../Resources/Sprites/";

	sf::Texture background;
	if (!background.loadFromFile(path + "Backgrounds/" + "wood6.png")) {
		//display error
		std::cout << "Error Loading File: wood6.jpg" << std::endl;
	} else {
		background.setRepeated(true);
		sf::Texture::bind(&background);
	}

	sf::Texture cardBack;
	if (!cardBack.loadFromFile(path + "Cards/Backs/" + "cardBack_red5.png")) {
		//display error
		std::cout << "Error Loading File: cardBack_green5.png" << std::endl;
	}
	else {
		sf::Texture::bind(&cardBack);
		cardBack.setSmooth(true);
	}

	sf::Texture cardHighlight;
	if (!cardHighlight.loadFromFile(path + "Cards/Backs/" + "Highlight2.png")) {
		//display error
		std::cout << "Error Loading File: Highlight2.png" << std::endl;
	}
	else {
		sf::Texture::bind(&cardHighlight);
		cardHighlight.setSmooth(true);
	}

	sf::Texture roundWon;
	if (!roundWon.loadFromFile(path + "Menus/Graphics/" + "RoundWon.png")) {
		//display error
		std::cout << "Error Loading File: RoundWon.jpg" << std::endl;
	}
	else {
		roundWon.setRepeated(true);
		sf::Texture::bind(&roundWon);
	}

	sf::Texture roundLost;
	if (!roundLost.loadFromFile(path + "Menus/Graphics/" + "RoundLost.png")) {
		//display error
		std::cout << "Error Loading File: RoundLost.png" << std::endl;
	}
	else {
		sf::Texture::bind(&roundLost);
		roundLost.setSmooth(true);
	}

	sf::Texture readyButton;
	if (!readyButton.loadFromFile(path + "Menus/Buttons/" + "Ready2.png")) {
		//display error
		std::cout << "Error Loading File: Ready2.png" << std::endl;
	}
	else {
		sf::Texture::bind(&readyButton);
		readyButton.setSmooth(true);
	}

	sf::Texture readySelected;
	if (!readySelected.loadFromFile(path + "Menus/Buttons/" + "ReadyS2.png")) {
		//display error
		std::cout << "Error Loading File: ReadyS2.png" << std::endl;
	}
	else {
		sf::Texture::bind(&readySelected);
		readySelected.setSmooth(true);
	}

	sf::Texture youWin;
	if (!youWin.loadFromFile(path + "Menus/Graphics/" + "YouWin2.png")) {
		//display error
		std::cout << "Error Loading File: YouWin2.png" << std::endl;
	}
	else {
		sf::Texture::bind(&youWin);
	}

	sf::Texture youLose;
	if (!youLose.loadFromFile(path + "Menus/Graphics/" + "YouLose.png")) {
		//display error
		std::cout << "Error Loading File: YouLose.png" << std::endl;
	}
	else {
		sf::Texture::bind(&youLose);
	}

	// main menu buttons

	sf::Texture playGame;
	if (!playGame.loadFromFile(path + "Menus/Buttons/" + "playGame.png")) {
		//display error
		std::cout << "Error Loading File: playGame.png" << std::endl;
	}
	else {
		playGame.setSmooth(true);
		sf::Texture::bind(&playGame);
	}

	sf::Texture options;
	if (!options.loadFromFile(path + "Menus/Buttons/" + "options.png")) {
		//display error
		std::cout << "Error Loading File: options.png" << std::endl;
	}
	else {
		options.setSmooth(true);
		sf::Texture::bind(&options);
	}

	sf::Texture exitApp;
	if (!exitApp.loadFromFile(path + "Menus/Buttons/" + "exitApp.png")) {
		//display error
		std::cout << "Error Loading File: exit.png" << std::endl;
	}
	else {
		exitApp.setSmooth(true);
		sf::Texture::bind(&exitApp);
	}

	//options menu buttons

	sf::Texture btnBack;
	if (!btnBack.loadFromFile(path + "Menus/Buttons/" + "back.png")) {
		//display error
		std::cout << "Error Loading File: back.png" << std::endl;
	}
	else {
		btnBack.setSmooth(true);
		sf::Texture::bind(&btnBack);
	}

	sf::Texture diffEasy;
	if (!diffEasy.loadFromFile(path + "Menus/Buttons/" + "diffEasy.png")) {
		//display error
		std::cout << "Error Loading File: diffEasy.png" << std::endl;
	}
	else {
		diffEasy.setSmooth(true);
		sf::Texture::bind(&diffEasy);
	}

	sf::Texture diffMedium;
	if (!diffMedium.loadFromFile(path + "Menus/Buttons/" + "diffMedium.png")) {
		//display error
		std::cout << "Error Loading File: diffMedium.png" << std::endl;
	}
	else {
		diffMedium.setSmooth(true);
		sf::Texture::bind(&diffMedium);
	}

	sf::Texture diffHard;
	if (!diffHard.loadFromFile(path + "Menus/Buttons/" + "diffHard.png")) {
		//display error
		std::cout << "Error Loading File: diffHard.png" << std::endl;
	}
	else {
		diffHard.setSmooth(true);
		sf::Texture::bind(&diffHard);
	}
	
	sf::Texture diffEasySel;
	if (!diffEasySel.loadFromFile(path + "Menus/Buttons/" + "diffEasyS.png")) {
		//display error
		std::cout << "Error Loading File: diffEasyS.png" << std::endl;
	}
	else {
		diffEasySel.setSmooth(true);
		sf::Texture::bind(&diffEasySel);
	}

	sf::Texture diffMediumSel;
	if (!diffMediumSel.loadFromFile(path + "Menus/Buttons/" + "diffMediumS.png")) {
		//display error
		std::cout << "Error Loading File: diffMediumS.png" << std::endl;
	}
	else {
		diffMediumSel.setSmooth(true);
		sf::Texture::bind(&diffMediumSel);
	}

	sf::Texture diffHardSel;
	if (!diffHardSel.loadFromFile(path + "Menus/Buttons/" + "diffHardS.png")) {
		//display error
		std::cout << "Error Loading File: diffHardS.png" << std::endl;
	}
	else {
		diffHardSel.setSmooth(true);
		sf::Texture::bind(&diffHardSel);
	}

	sf::Texture skillRookie;
	if (!skillRookie.loadFromFile(path + "Menus/Buttons/" + "skillRookie.png")) {
		//display error
		std::cout << "Error Loading File: skillRookie.png" << std::endl;
	}
	else {
		skillRookie.setSmooth(true);
		sf::Texture::bind(&skillRookie);
	}

	sf::Texture skillInter;
	if (!skillInter.loadFromFile(path + "Menus/Buttons/" + "skillIntermediate.png")) {
		//display error
		std::cout << "Error Loading File: skillIntermediate.png" << std::endl;
	}
	else {
		skillInter.setSmooth(true);
		sf::Texture::bind(&skillInter);
	}

	sf::Texture skillVeteran;
	if (!skillVeteran.loadFromFile(path + "Menus/Buttons/" + "skillVeteran.png")) {
		//display error
		std::cout << "Error Loading File: skillVeteran.png" << std::endl;
	}
	else {
		skillVeteran.setSmooth(true);
		sf::Texture::bind(&skillVeteran);
	}

	sf::Texture skillMaster;
	if (!skillMaster.loadFromFile(path + "Menus/Buttons/" + "skillMaster.png")) {
		//display error
		std::cout << "Error Loading File: skillMaster.png" << std::endl;
	}
	else {
		skillMaster.setSmooth(true);
		sf::Texture::bind(&skillMaster);
	}

	sf::Texture skillRookieSel;
	if (!skillRookieSel.loadFromFile(path + "Menus/Buttons/" + "skillRookieS.png")) {
		//display error
		std::cout << "Error Loading File: skillRookieS.png" << std::endl;
	}
	else {
		skillRookieSel.setSmooth(true);
		sf::Texture::bind(&skillRookieSel);
	}

	sf::Texture skillInterSel;
	if (!skillInterSel.loadFromFile(path + "Menus/Buttons/" + "skillIntermediateS.png")) {
		//display error
		std::cout << "Error Loading File: skillIntermediateS.png" << std::endl;
	}
	else {
		skillInterSel.setSmooth(true);
		sf::Texture::bind(&skillInterSel);
	}

	sf::Texture skillVeteranSel;
	if (!skillVeteranSel.loadFromFile(path + "Menus/Buttons/" + "skillVeteranS.png")) {
		//display error
		std::cout << "Error Loading File: skillVeteranS.png" << std::endl;
	}
	else {
		skillVeteranSel.setSmooth(true);
		sf::Texture::bind(&skillVeteranSel);
	}

	sf::Texture skillMasterSel;
	if (!skillMasterSel.loadFromFile(path + "Menus/Buttons/" + "skillMasterS.png")) {
		//display error
		std::cout << "Error Loading File: skillMaster.png" << std::endl;
	}
	else {
		skillMasterSel.setSmooth(true);
		sf::Texture::bind(&skillMasterSel);
	}

	//=================================
	// text and shape creation
	sf::Text title1;
	title1.setFont(carved);
	title1.setFillColor(sf::Color(255, 130, 63));
	title1.setString("AUTHENTIC");
	title1.setCharacterSize(70);
	title1.setPosition(200,50);

	sf::Text title2;
	title2.setFont(carved);
	title2.setFillColor(sf::Color(255, 179, 135));
	title2.setString("SPIT");
	title2.setCharacterSize(70);
	title2.setPosition(320, 110);

	sf::Text optionsTitle;
	optionsTitle.setFont(carved);
	optionsTitle.setFillColor(sf::Color(255, 179, 135));
	optionsTitle.setString("OPTIONS");
	optionsTitle.setCharacterSize(80);
	optionsTitle.setPosition(225, 30);

	sf::CircleShape circleBack(34);
	circleBack.setFillColor(sf::Color(255, 255, 255));
	circleBack.setOutlineThickness(4);
	circleBack.setOutlineColor(sf::Color(194, 198, 206));
	circleBack.setPosition(20, 20);

	sf::Text difficultyTitle;
	difficultyTitle.setFont(carved);
	difficultyTitle.setFillColor(sf::Color(255, 130, 63));
	difficultyTitle.setString("AI DIFFICULTY");
	difficultyTitle.setCharacterSize(40);
	difficultyTitle.setPosition(240, 140);

	sf::Text difficultyText;
	difficultyText.setFont(carved);
	difficultyText.setFillColor(sf::Color(255, 255, 255));
	difficultyText.setString("DETERMINES HOW FAST THE AI CAN REACT");
	difficultyText.setCharacterSize(20);
	difficultyText.setPosition(180, 190);

	sf::RectangleShape rectDiff(sf::Vector2f(600, 180));
	rectDiff.setPosition(sf::Vector2f(100, 140));
	rectDiff.setFillColor(sf::Color(66, 134, 144, 180));

	sf::Text skillTitle;
	skillTitle.setFont(carved);
	skillTitle.setFillColor(sf::Color(255, 130, 63));
	skillTitle.setString("AI SKILL");
	skillTitle.setCharacterSize(40);
	skillTitle.setPosition(300, 350);

	sf::Text skillText;
	skillText.setFont(carved);
	skillText.setFillColor(sf::Color(255, 255, 255));
	skillText.setString("DETERMINES THE INTELLIGENCE OF THE AI OPPONENT");
	skillText.setCharacterSize(20);
	skillText.setPosition(120, 400);

	sf::RectangleShape rectSkill(sf::Vector2f(600, 180));
	rectSkill.setPosition(sf::Vector2f(100, 350));
	rectSkill.setFillColor(sf::Color(66, 244, 98, 180));

	sf::RectangleShape rectangle(sf::Vector2f(300, 220));
	rectangle.setPosition(sf::Vector2f(250, 100));
	rectangle.setFillColor(sf::Color(66, 134, 144, 128));

	sf::RectangleShape shadow(sf::Vector2f(112, 156));
	shadow.setFillColor(sf::Color(0, 0, 0, 90));

	//=================================
	// sprite creation
	sf::Sprite backgroundS;
	backgroundS.setTextureRect(sf::IntRect(0,0,800,600));
	backgroundS.setTexture(background);

	sf::Sprite cardBackS;
	cardBackS.setTexture(cardBack);
	cardBackS.setScale(0.8f, 0.821f);	

	sf::Sprite cardHighlightS;
	cardHighlightS.setTexture(cardHighlight);
	cardHighlightS.setScale(1.1f, 1.06f);

	sf::Sprite roundWonS;
	roundWonS.setTexture(roundWon);
	roundWonS.setScale(0.6f, 0.6f);
	roundWonS.setPosition(sf::Vector2f(241.6f, 249.5));

	sf::Sprite roundLostS;
	roundLostS.setTexture(roundLost);
	roundLostS.setScale(0.6f, 0.6f);
	roundLostS.setPosition(sf::Vector2f(237.7f, 249.5));

	sf::Sprite readyButtonS;
	readyButtonS.setTexture(readyButton);
	readyButtonS.setScale(0.7f, 0.7f);

	sf::Sprite readySelectedS;
	readySelectedS.setTexture(readySelected);
	readySelectedS.setScale(0.7f, 0.7f);

	sf::Sprite youWinS;
	youWinS.setTexture(youWin);
	youWinS.setPosition(sf::Vector2f(298,145));

	sf::Sprite youLoseS;
	youLoseS.setTexture(youLose);
	youLoseS.setPosition(sf::Vector2f(335, 146));	

	// main menu

	sf::Sprite playGameS;
	playGameS.setTexture(playGame);
	playGameS.setPosition(sf::Vector2f(288, 270));

	sf::Sprite optionsS;
	optionsS.setTexture(options);
	optionsS.setPosition(sf::Vector2f(311.5f, 380));

	sf::Sprite exitAppS;
	exitAppS.setTexture(exitApp);
	exitAppS.setPosition(sf::Vector2f(308.5, 490));

	// options

	sf::Sprite btnBackS;
	btnBackS.setTexture(btnBack);	

	sf::Sprite diffEasyS;
	diffEasyS.setTexture(diffEasy);
	diffEasyS.setPosition(sf::Vector2f(130, 240));

	sf::Sprite diffMediumS;
	diffMediumS.setTexture(diffMedium);
	diffMediumS.setPosition(sf::Vector2f(325, 240));

	sf::Sprite diffHardS;
	diffHardS.setTexture(diffHard);
	diffHardS.setPosition(sf::Vector2f(559, 240));

	sf::Sprite skillRookieS;
	skillRookieS.setTexture(skillRookie);
	skillRookieS.setPosition(sf::Vector2f(112, 455));

	sf::Sprite skillInterS;
	skillInterS.setTexture(skillInter);
	skillInterS.setPosition(sf::Vector2f(237.5f, 455));

	sf::Sprite skillVeteranS;
	skillVeteranS.setTexture(skillVeteran);
	skillVeteranS.setPosition(sf::Vector2f(422, 455));

	sf::Sprite skillMasterS;
	skillMasterS.setTexture(skillMaster);
	skillMasterS.setPosition(sf::Vector2f(557.5, 455));

	// selected options

	sf::Sprite diffEasySelS;
	diffEasySelS.setTexture(diffEasySel);
	diffEasySelS.setPosition(sf::Vector2f(130, 240));

	sf::Sprite diffMediumSelS;
	diffMediumSelS.setTexture(diffMediumSel);
	diffMediumSelS.setPosition(sf::Vector2f(325, 240));

	sf::Sprite diffHardSelS;
	diffHardSelS.setTexture(diffHardSel);
	diffHardSelS.setPosition(sf::Vector2f(559, 240));

	sf::Sprite skillRookieSelS;
	skillRookieSelS.setTexture(skillRookieSel);
	skillRookieSelS.setPosition(sf::Vector2f(112, 455));

	sf::Sprite skillInterSelS;
	skillInterSelS.setTexture(skillInterSel);
	skillInterSelS.setPosition(sf::Vector2f(237.5f, 455));

	sf::Sprite skillVeteranSelS;
	skillVeteranSelS.setTexture(skillVeteranSel);
	skillVeteranSelS.setPosition(sf::Vector2f(422, 455));

	sf::Sprite skillMasterSelS;
	skillMasterSelS.setTexture(skillMasterSel);
	skillMasterSelS.setPosition(sf::Vector2f(557.5, 455));

	//=================================
	// sound buffer creation

	path = "\../Resources/Sounds/";

	sf::SoundBuffer cardPlace1B;
	if (!cardPlace1B.loadFromFile(path + "cardPlace1.ogg")) {
		//display error
		std::cout << "Error Loading File: cardPlace1.ogg" << std::endl;
	}
	else {

	}

	sf::SoundBuffer cardPlace2B;
	if (!cardPlace2B.loadFromFile(path + "cardPlace2.ogg")) {
		//display error
		std::cout << "Error Loading File: cardPlace2.ogg" << std::endl;
	}
	else {

	}

	sf::SoundBuffer cardSlide2B;
	if (!cardSlide2B.loadFromFile(path + "cardSlide2.ogg")) {
		//display error
		std::cout << "Error Loading File: cardSlide2.ogg" << std::endl;
	}
	else {

	}

	sf::SoundBuffer cardSlide3B;
	if (!cardSlide3B.loadFromFile(path + "cardSlide3.ogg")) {
		//display error
		std::cout << "Error Loading File: cardSlide3.ogg" << std::endl;
	}
	else {

	}

	//=================================
	// sound creation

	sf::Sound cardPlace1;
	cardPlace1.setBuffer(cardPlace1B);
	cardPlace1.setVolume(50);

	sf::Sound cardPlace2;
	cardPlace2.setBuffer(cardPlace2B);
	cardPlace2.setVolume(50);

	sf::Sound cardPlace3;
	cardPlace3.setBuffer(gameAI.getCardPlace3());
	cardPlace3.setVolume(50);

	sf::Sound cardSlide2;
	cardSlide2.setBuffer(cardSlide2B);
	cardSlide2.setVolume(50);
	
	sf::Sound cardSlide3;
	cardSlide3.setBuffer(gameAI.getCardSlide3());
	cardSlide3.setVolume(50);

	// pre-defining SFML and openGL settings
	sf::VideoMode video = sf::VideoMode(800, 600);

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	// window creation
	sf::RenderWindow window(video, "SFML Honours", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	// window activation
	window.setActive(true);

	//sets the clock
	sf::Clock clock;
	sf::Clock refresh;
	sf::Clock aIPlayClock;
	sf::Clock aIOtherClock;

	while (window.isOpen()) 
	{
		// prints response time in milliseconds
		sf::Time elapsed = clock.restart();
		std::cout << elapsed.asMilliseconds() << std::endl;

		//=================================
		// === event handling ===

		sf::Event event;
		while (window.pollEvent(event)) {

			// general application events
			// checks the event type
			switch (event.type) {

				// window closed
			case sf::Event::Closed:
				playingStatus = false;
				window.close();
				break;
				// window re-sized
			case sf::Event::Resized:
				// adjusts viewport size with the window
				glViewport(0, 0, event.size.width, event.size.height);
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
				break;

				// default case
			default:
				break;
			}
			
			// game event handling
			if (appState == "Game") {

				switch (event.type) {

					// when a mouse button is pressed
					case event.MouseButtonPressed:

						// if the left mouse button is pressed
						if (event.mouseButton.button == sf::Mouse::Left) {

							// back button selected
							if ((event.mouseButton.x >= 5 and event.mouseButton.x <= 41)
								and (event.mouseButton.y >= 5 and event.mouseButton.y <= 41)) {
								
								appState = "MainMenu";
								gameState = "Pre-Round";

								newDeck.wipe();
								gameDeck1.wipe();
								gameDeck2.wipe();
								player1Deck.wipe();
								player2Deck.wipe();
								player1Hand.wipe();
								player2Hand.wipe();
								playingStatus = false;

							}


							// if hand pile 1 is selected
							if ((event.mouseButton.x >= 50 and event.mouseButton.x <= 182)
								and (event.mouseButton.y >= 416 and event.mouseButton.y <= (592 +
								((player1Hand.getHand1().size() - 1) * 2)))
								and player1Hand.getHand1().size() > 0) {
								
								player1Hand.setHand1Selected();
								
								std::cout << "Handpile1 selected" << std::endl;
							}
							// if hand pile 2 is selected
							else if ((event.mouseButton.x >= 192 and event.mouseButton.x <= 324)
								and (event.mouseButton.y >= 416 and event.mouseButton.y <= (592 +
								((player1Hand.getHand2().size() - 1) * 2)))
								and player1Hand.getHand2().size() > 0) {
								if (player1Hand.getHand2().topCard().getVisible() == true) {
									player1Hand.setHand2Selected();
								}
								else {
									cardPlace2.play();
									player1Hand.hand2FlipTopC();
								}
								std::cout << "Handpile2 selected" << std::endl;
							}
							// if hand pile 3 is selected
							else if ((event.mouseButton.x >= 334 and event.mouseButton.x <= 466)
								and (event.mouseButton.y >= 416 and event.mouseButton.y <= (592 +
								((player1Hand.getHand3().size() - 1) * 2)))
								and player1Hand.getHand3().size() > 0) {
								if (player1Hand.getHand3().topCard().getVisible() == true) {
									player1Hand.setHand3Selected();
								}
								else {
									cardPlace2.play();
									player1Hand.hand3FlipTopC();
								}
								std::cout << "Handpile3 selected" << std::endl;
							}
							// if hand pile 4 is selected
							else if ((event.mouseButton.x >= 476 and event.mouseButton.x <= 608)
								and (event.mouseButton.y >= 416 and event.mouseButton.y <= (592 +
								((player1Hand.getHand4().size() - 1) * 2)))
								and player1Hand.getHand4().size() > 0) {
								if (player1Hand.getHand4().topCard().getVisible() == true) {
									player1Hand.setHand4Selected();
								}
								else {
									cardPlace2.play();
									player1Hand.hand4FlipTopC();
								}
								std::cout << "Handpile4 selected" << std::endl;
							}
							// if hand pile 5 is selected
							else if ((event.mouseButton.x >= 618 and event.mouseButton.x <= 750)
								and (event.mouseButton.y >= 416 and event.mouseButton.y <= (592 +
								((player1Hand.getHand5().size() - 1) * 2)))
								and player1Hand.getHand5().size() > 0) {
								if (player1Hand.getHand5().topCard().getVisible() == true) {
									player1Hand.setHand5Selected();
								}
								else {
									cardPlace2.play();
									player1Hand.hand5FlipTopC();
								}
								std::cout << "Handpile5 selected" << std::endl;
							}

							//if game piles require refreshing and player clicks their deck
							else if ((((player1Hand.countCards() != 0 and player2Hand.countCards() != 0)
									and (player1Hand.canPlay(gameDeck1, gameDeck2)
										+ player2Hand.canPlay(gameDeck1, gameDeck2)) == false
										and playingStatus == true
										and ((player1Hand.allTopCardsVisible() || player1Hand.allCardsVisible())
											and (player2Hand.allTopCardsVisible() || player2Hand.allCardsVisible()))
								and refresh.getElapsedTime() > sf::seconds(1))
								|| gameState == "Pre-Round")
								and (event.mouseButton.x >= 632 and event.mouseButton.x <= 744)
								and (event.mouseButton.y >= 222 and event.mouseButton.y <= 378)) {

								//starts or resumes the round
								if (player1Deck.size() > 0) {
									player1Deck.play(gameDeck2);
									cardPlace2.play();
								}

								if (player2Deck.size() > 0) {
									player2Deck.play(gameDeck1);
									cardPlace3.play();
								}								
								
								gameState = "In Game";
								playingStatus = true;
								refresh.restart();
								aIPlayReaction = calcAIPlaySpeed(aIDifficulty);
								aIPlayClock.restart();
							}
						}//end if left mouse button statement
					break;//end mouse button case statement
					
					// when a mouse button is released
					case event.MouseButtonReleased: 

						//if the left mouse button is released
						if (event.mouseButton.button == sf::Mouse::Left) {

							//retrieves the selected hand, if there is one
							HandPile *selectedPile = player1Hand.getHandSelected();

							//if a hand is selected
							if (selectedPile->getSelected() == true) {

								// if a card is released on gameDeck1
								if ((event.mouseButton.x >= 217 and event.mouseButton.x <= 359)
									and (event.mouseButton.y >= 207 and event.mouseButton.y <= 393)
									and playingStatus == true) {
									if (selectedPile->isPlayable(gameDeck1)) {
										
										//resets the AI's wait time
										if (gameAI.getChosenGDeck() == "GameDeck1"
											|| !gameAI.getCardPlayable()
											|| !player2Hand.canPlay(gameDeck1, gameDeck2)) {
											aIPlayReaction = calcAIPlaySpeed(aIDifficulty);
											aIPlayClock.restart();
										}
										
										refresh.restart();
										cardPlace1.play();
										selectedPile->place(gameDeck1);
									}
								}
								// if a card is released on gameDeck2
								else if ((event.mouseButton.x >= 441 and event.mouseButton.x <= 583)
									and (event.mouseButton.y >= 207 and event.mouseButton.y <= 392)
									and playingStatus == true) {
									if (selectedPile->isPlayable(gameDeck2)) {
										
										if (gameAI.getChosenGDeck() == "GameDeck2"
											|| !gameAI.getCardPlayable()
											|| !player2Hand.canPlay(gameDeck1, gameDeck2)) {
											aIPlayReaction = calcAIPlaySpeed(aIDifficulty);
											aIPlayClock.restart();
										}

										refresh.restart();
										cardPlace1.play();
										selectedPile->place(gameDeck2);										
									}
								}
								// if a card is released on p1Hand1
								else if ((event.mouseButton.x >= 55 and event.mouseButton.x <= 177)
									and (event.mouseButton.y >= 421 and event.mouseButton.y <= 587)
									and selectedPile->getID() != 1) {
									if (selectedPile->stockpile(&player1Hand.getHand1())) {
										cardSlide3.play();
									}
								}

								// if a card is released on p1Hand2
								else if ((event.mouseButton.x >= 197 and event.mouseButton.x <= 319)
									and (event.mouseButton.y >= 421 and event.mouseButton.y <= 587)
									and selectedPile->getID() != 2) {
									if (selectedPile->stockpile(&player1Hand.getHand2())) {
										cardSlide3.play();
									}
								}

								// if a card is released on p1Hand3
								else if ((event.mouseButton.x >= 339 and event.mouseButton.x <= 461)
									and (event.mouseButton.y >= 421 and event.mouseButton.y <= 587)
									and selectedPile->getID() != 3) {
									if (selectedPile->stockpile(&player1Hand.getHand3())) {
										cardSlide3.play();
									}
								}

								// if a card is released on p1Hand4
								else if ((event.mouseButton.x >= 481 and event.mouseButton.x <= 603)
									and (event.mouseButton.y >= 421 and event.mouseButton.y <= 587)
									and selectedPile->getID() != 4) {
									if (selectedPile->stockpile(&player1Hand.getHand4())) {
										cardSlide3.play();
									}
								}

								// if a card is released on p1Hand5
								else if ((event.mouseButton.x >= 623 and event.mouseButton.x <= 745)
									and (event.mouseButton.y >= 421 and event.mouseButton.y <= 587)
									and selectedPile->getID() != 5) {
									if (selectedPile->stockpile(&player1Hand.getHand5())) {
										cardSlide3.play();
									}
								}
							} // end if card selected

							// if no card is selected and Spit is possible
							else if (gameState == "SPIT") {

								// spits on gameDeck1 and sets up the next round
								if ((event.mouseButton.x >= 232 and event.mouseButton.x <= 344)
									and (event.mouseButton.y >= 222 and event.mouseButton.y <= 378)) {
									gameDeck1.dumpDeck(player1Deck);
									gameDeck2.dumpDeck(player2Deck);
									player1Hand.clearHand(&player1Deck);
									player2Hand.clearHand(&player2Deck);
									
									// determines if the game has ended
									if (player1Deck.size() == 0
										|| player2Deck.size() == 0) {

										//resets game variables
										newDeck.wipe();
										player1Deck.wipe();
										player2Deck.wipe();
										player1Hand.wipe();
										player2Hand.wipe();
										playingStatus = false;
										gameState = "End";

										//displays a win or loss screen depending or result
										if (player1Deck.size() == 0) {
											condition = "Win";
										}
										else {
											condition = "Lose";
										}

									}
									else {
										player1Deck.dealHand(&player1Hand.getHand1(), &player1Hand.getHand2(), &player1Hand.getHand3(), &player1Hand.getHand4(), &player1Hand.getHand5());
										player2Deck.dealHand(&player2Hand.getHand1(), &player2Hand.getHand2(), &player2Hand.getHand3(), &player2Hand.getHand4(), &player2Hand.getHand5());
										playingStatus = false;
										gameState = "Pre-Round";
										displayResult = true;
										result = roundWonS;
										a = 255;
									}

								}
								// spits on gameDeck2 and sets up the next round
								else if ((event.mouseButton.x >= 456 and event.mouseButton.x <= 568)
									and (event.mouseButton.y >= 222 and event.mouseButton.y <= 378)) {
									gameDeck1.dumpDeck(player2Deck);
									gameDeck2.dumpDeck(player1Deck);
									player1Hand.clearHand(&player1Deck);
									player2Hand.clearHand(&player2Deck);
									
									// determines if the game has ended
									if (player1Deck.size() == 0
										|| player2Deck.size() == 0) {

										//resets game variables
										newDeck.wipe();
										player1Deck.wipe();
										player2Deck.wipe();
										player1Hand.wipe();
										player2Hand.wipe();
										playingStatus = false;
										gameState = "End";

										//displays a win or loss screen depending or result
										if (player1Deck.size() == 0) {
											condition = "Win";
										}
										else {
											condition = "Lose";
										}

									}
									else {
										player1Deck.dealHand(&player1Hand.getHand1(), &player1Hand.getHand2(), &player1Hand.getHand3(), &player1Hand.getHand4(), &player1Hand.getHand5());
										player2Deck.dealHand(&player2Hand.getHand1(), &player2Hand.getHand2(), &player2Hand.getHand3(), &player2Hand.getHand4(), &player2Hand.getHand5());
										playingStatus = false;
										gameState = "Pre-Round";
										displayResult = true;
										result = roundWonS;
										a = 255;
									}

								}
							}
							
							selectedPile->setSelected(false);
						}
					break;//end mouseButtonReleased case statement
					
						  // default case
					default:
						break;

				}//end event type switch statement
			}//end if playing statement
			else if (appState == "MainMenu") {

				switch (event.type) {

					// when a mouse button is pressed
				case event.MouseButtonPressed:

					// if the left mouse button is pressed
					if (event.mouseButton.button == sf::Mouse::Left) {

						// plays the game
						if ((event.mouseButton.x >= 288 and event.mouseButton.x <= 512)
							and (event.mouseButton.y >= 270 and event.mouseButton.y <= 334)) {
							
							appState = "Game";

							//=================================
							// game setup
														
							gameState = "Pre-Round";

							//creates and prints the initial deck
							newDeck.createDeck();
							newDeck.toString();

							//deals the deck's contents out to either player
							newDeck.deal(player1Deck, player2Deck);

							//shuffles each players' deck
							player1Deck.shuffle();
							player2Deck.shuffle();

							//deals each player 15 cards
							player1Deck.dealHand(&player1Hand.getHand1(), &player1Hand.getHand2(), &player1Hand.getHand3(), &player1Hand.getHand4(), &player1Hand.getHand5());
							player2Deck.dealHand(&player2Hand.getHand1(), &player2Hand.getHand2(), &player2Hand.getHand3(), &player2Hand.getHand4(), &player2Hand.getHand5());

							//adjusts shapes and sprites for page
							circleBack.setRadius(18);
							circleBack.setPosition(sf::Vector2f(10, 10));

							btnBackS.setScale(0.25f, 0.25f);
							btnBackS.setPosition(sf::Vector2f(16, 17));

						}
						// changes to the options screen
						else if ((event.mouseButton.x >= 311 and event.mouseButton.x <= 488)
							and (event.mouseButton.y >= 380 and event.mouseButton.y <= 444)) {
							appState = "Options";

							//adjusts shapes and sprites for page
							circleBack.setRadius(34);
							circleBack.setPosition(20, 20);

							btnBackS.setScale(0.5f, 0.5f);
							btnBackS.setPosition(sf::Vector2f(30, 32));

						}
						// closes the application
						else if ((event.mouseButton.x >= 308 and event.mouseButton.x <= 491)
							and (event.mouseButton.y >= 490 and event.mouseButton.y <= 554)) {
							window.close();
						}

					}
				break;

				}
			}
			else if (appState == "Options") {

				switch (event.type) {

					// when a mouse button is pressed
				case event.MouseButtonPressed:

					// if the left mouse button is pressed
					if (event.mouseButton.button == sf::Mouse::Left) {

						if (event.mouseButton.y >= 240 and event.mouseButton.y <= 294) {
							if (event.mouseButton.x >= 130 and event.mouseButton.x <= 236) {
								aIDifficulty = "Easy";
							}
							else if (event.mouseButton.x >= 325 and event.mouseButton.x <= 476) {
								aIDifficulty = "Medium";
							}
							else if (event.mouseButton.x >= 559 and event.mouseButton.x <= 670) {
								aIDifficulty = "Hard";
							}
							gameAI.setDifficulty(aIDifficulty);
						}
						else if (event.mouseButton.y >= 455 and event.mouseButton.y <= 501) {
							if (event.mouseButton.x >= 112 and event.mouseButton.x <= 223) {
								aISkill = "Rookie";
							}
							else if (event.mouseButton.x >= 237.5 and event.mouseButton.x <= 407.5) {
								aISkill = "Intermediate";
							}
							else if (event.mouseButton.x >= 422 and event.mouseButton.x <= 543) {
								aISkill = "Veteran";
							}
							else if (event.mouseButton.x >= 557.5 and event.mouseButton.x <= 673.5) {
								aISkill = "Master";
							}
							gameAI.setSkill(aISkill);
						}
						else if ((event.mouseButton.x >= 20 and event.mouseButton.x <= 88)
							and (event.mouseButton.y >= 20 and event.mouseButton.y <= 88)) {
							appState = "MainMenu";
						}
					}
					break;

				}
			}
		}//end event handling while loop

		//=================================
		// === update === 

		// clears the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		glEnable(GL_TEXTURE_2D);

		window.pushGLStates();

		//draws background
		window.draw(backgroundS);
				
		if (appState == "Game") {

			// displays GameDeck1 on the left hand side
			for (int i = 0; i < gameDeck1.size(); i++) {

				//highlights the deck if a player has no cards in their hand
				if (i == gameDeck1.size() - 1
					and gameState == "SPIT"
					and playingStatus == true) {

					//sets the sprite's position over the top card
					cardHighlightS.setPosition((float)227, (float)(217 - gameDeck1.size() + (2 * i)));

					//draws the sprite
					window.draw(cardHighlightS);
				}

				//sets the card's position, placing it 2 pixels below the last card
				gameDeck1.setPosition(i, sf::Vector2f((float)232, (float)(222 - gameDeck1.size() + (2 * i))));

				//draws the sprite
				window.draw(gameDeck1.getFullDeck()[i].getSprite());

			}

			// displays GameDeck2 on the right hand side
			for (int i = 0; i < gameDeck2.size(); i++) {

				//highlights the deck if a player has no cards in their hand
				if (i == gameDeck2.size() - 1
					and gameState == "SPIT"
					and playingStatus == true) {

					//sets the sprite's position over the top card
					cardHighlightS.setPosition((float)451, (float)(217 - gameDeck2.size() + (2 * i)));

					//draws the sprite
					window.draw(cardHighlightS);
				}

				//sets the card's position, placing it 2 pixels below the last card
				gameDeck2.setPosition(i, sf::Vector2f((float)456, (float)(222 - gameDeck2.size() + (2 * i))));

				//draws the sprite
				window.draw(gameDeck2.getFullDeck()[i].getSprite());

			}

			//runs the thread whilst the main is displaying the other player's cards.
			if (gameState == "In Game") {
				playHand = std::thread(&AI::playHand, &gameAI);
			}

			//Highlights the space where cards would be if a pileis empty during a spit situation
			if (gameState == "SPIT"
				and playingStatus == true) {

				//determines which deck is empty and sets the sprite's position to it
				if (gameDeck1.size() == 0) {
					cardHighlightS.setPosition((float)227, (float)(217));
				}
				else if (gameDeck2.size() == 0) {
					cardHighlightS.setPosition((float)451, (float)(217));
				}
				//draws the sprite
				window.draw(cardHighlightS);
			}			

			// displays Player1Deck on the right hand side
			for (int i = 0; i < player1Deck.size(); i++) {

				//sets the card's position, placing it 2 pixels below the last card
				cardBackS.setPosition((float)632, (float)(222 - player1Deck.size() + (2 * i)));

				//draws the sprite
				window.draw(cardBackS);
			}

			//highlights player1Deck if it is empty
			if (((player1Hand.canPlay(gameDeck1, gameDeck2)
					+ player2Hand.canPlay(gameDeck1, gameDeck2)) == false
					and (player1Hand.countCards() != 0 and player2Hand.countCards() != 0)
					and playingStatus == true
					and ((player1Hand.allTopCardsVisible() || player1Hand.allCardsVisible())
						and (player2Hand.allTopCardsVisible() || player2Hand.allCardsVisible()))
					and refresh.getElapsedTime() > sf::seconds(1))
				|| gameState == "Pre-Round") {

				int i = player1Deck.size() - 1;

				// sets the sprite's position over the deck
				cardHighlightS.setPosition((float)627, (float)(217 - player1Deck.size() + (2 * i)));

				//draws the sprite
				window.draw(cardHighlightS);

			}

			// displays Player2Deck on the left hand side
			for (int i = 0; i < player2Deck.size(); i++) {

				//sets the card's position, placing it 2 pixels below the last card
				cardBackS.setPosition((float)60, (float)(222 - player2Deck.size() + (2 * i)));

				//draws the sprite
				window.draw(cardBackS);
			}

			// WHERE PLAYHAND THREAD WAS RAN BEFORE		


			// displays Player1's first hand pile
			drawPlayerHand(&player1Hand, &window, cardBackS, 1, 60, 426);

			 // displays Player1's second hand pile
			drawPlayerHand(&player1Hand, &window, cardBackS, 2, 202, 426);
			
			 // displays Player1's third hand pile
			drawPlayerHand(&player1Hand, &window, cardBackS, 3, 344, 426);
			
			 // displays Player1's fourth hand pile
			drawPlayerHand(&player1Hand, &window, cardBackS, 4, 486, 426);

			 // displays Player1's fifth hand pile
			drawPlayerHand(&player1Hand, &window, cardBackS, 5, 628, 426);
			
			std::cout << aIPlayReaction.asMilliseconds() << std::endl;
			std::cout << aIPlayClock.getElapsedTime().asMilliseconds() << std::endl;

			// AI FUNCTIONS ~~~~~
			//joins threads before displaying player2's cards
			if (playHand.joinable()) {
				playHand.join();
			}
				

			// checks if the AI can spit 
			if (gameState != "SPIT") {

				// if the AI has waited long enough for it's reaction
				if (aIPlayClock.getElapsedTime() >= aIPlayReaction
					and gameState == "In Game") {

					if (gameAI.playCard()) {
						aIPlayReaction = calcAIPlaySpeed(aIDifficulty);

						refresh.restart();
						aIPlayClock.restart();
						aIOtherClock.restart();
					}
					
				}

			}
			else {
				// if the AI has waited long enough for it's reaction
				if (aIOtherClock.getElapsedTime() >= aIOtherReaction) {

					//determines which gameDeck the AI will spit on
					if (gameDeck1.size() <= gameDeck2.size()) {
						gameDeck1.dumpDeck(player2Deck);
						gameDeck2.dumpDeck(player1Deck);
					}
					else {
						gameDeck1.dumpDeck(player1Deck);
						gameDeck2.dumpDeck(player2Deck);
					}

					player1Hand.clearHand(&player1Deck);
					player2Hand.clearHand(&player2Deck);

					//checks to see if either player has won the game
					if (player1Deck.size() == 0
						|| player2Deck.size() == 0) {
						playingStatus = false;
						gameState = "End";
						if (player1Deck.size() == 0) {
							condition = "Win";
						}
						else {
							condition = "Lose";
						}
					}
					else {
						//sets up the next round
						player1Deck.dealHand(&player1Hand.getHand1(), &player1Hand.getHand2(), &player1Hand.getHand3(), &player1Hand.getHand4(), &player1Hand.getHand5());
						player2Deck.dealHand(&player2Hand.getHand1(), &player2Hand.getHand2(), &player2Hand.getHand3(), &player2Hand.getHand4(), &player2Hand.getHand5());
						playingStatus = false;
						gameState = "Pre-Round";
						displayResult = true;
						result = roundLostS;
						a = 255;
					}


				}
			}

			 // displays Player2's first hand pile
			drawOpponentHand(&player2Hand, &window, cardBackS, 1, 628, 20);			

			// displays Player2's second hand pile
			drawOpponentHand(&player2Hand, &window, cardBackS, 2, 486, 20);

			// displays Player2's third hand pile
			drawOpponentHand(&player2Hand, &window, cardBackS, 3, 344, 20);

			// displays Player2's fourth hand pile
			drawOpponentHand(&player2Hand, &window, cardBackS, 4, 202, 20);

			// displays Player2's fifth hand pile
			drawOpponentHand(&player2Hand, &window, cardBackS, 5, 60, 20);
			
			window.draw(circleBack);
			window.draw(btnBackS);

			if (gameState == "End") {

				window.draw(rectangle);

				if (condition == "Win") {
					window.draw(youWinS);
				}
				else {
					window.draw(youLoseS);
				}
			}


			if (aIOtherClock.getElapsedTime() >= aIOtherReaction
				and gameState != "SPIT") {

				//otherHand = std::thread(&AI::otherHand, &gameAI);

				//resets the playClock if the AI cannot currently play
				if (!gameAI.getCardPlayable()) {
					aIPlayReaction = calcAIPlaySpeed(aIDifficulty);
					aIPlayClock.restart();
				}

				gameAI.otherHand();

				aIOtherReaction = calcAIOtherSpeed(aIDifficulty);
				aIOtherClock.restart();
			}

			if ((player1Hand.countCards() == 0
				|| player2Hand.countCards() == 0)
				and gameState == "In Game") {

				gameState = "SPIT";

				aIOtherReaction = calcAIOtherSpeed(aIDifficulty);

				aIOtherClock.restart();

			}

			//if (otherHand.joinable()) {
			//otherHand.join();
			//}

			// gets the selected pile
			HandPile *pileSelected = player1Hand.getHandSelected();

			// sets the selected card's position under the mouse whilst it is selected
			if (pileSelected->getSelected() == true) {
				tempCard = pileSelected->topCard();
				sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
				pos.x -= 56;
				pos.y -= 78;
				tempCard.setPosition(pos);
				pos.x += 8;
				pos.y += 8;
				shadow.setPosition(pos);
				window.draw(shadow);
				window.draw(tempCard.getSprite());
			}

			if (displayResult == true) {
				
				result.setColor(sf::Color(255, 255, 255, a));
				window.draw(result);

				a -= 3;
				if (a <= 0) {
					displayResult = false;
				}
			}

		}
		else if (appState == "MainMenu") {
			window.draw(title1);
			window.draw(title2);

			window.draw(playGameS);

			window.draw(optionsS);

			window.draw(exitAppS);

		}
		else if (appState == "Options") {
			window.draw(optionsTitle);
			window.draw(circleBack);
			window.draw(btnBackS);

			window.draw(rectDiff);
			window.draw(difficultyTitle);
			window.draw(difficultyText);

			if (aIDifficulty == "Easy") {
				window.draw(diffEasySelS);
				window.draw(diffMediumS);
				window.draw(diffHardS);
			}
			else if (aIDifficulty == "Medium") {
				window.draw(diffEasyS);
				window.draw(diffMediumSelS);
				window.draw(diffHardS);
			}
			else {
				window.draw(diffEasyS);
				window.draw(diffMediumS);
				window.draw(diffHardSelS);
			}
			

			window.draw(rectSkill);
			window.draw(skillTitle);
			window.draw(skillText);

			if (aISkill == "Rookie") {
				window.draw(skillRookieSelS);
				window.draw(skillInterS);
				window.draw(skillVeteranS);
				window.draw(skillMasterS);
			}
			else if (aISkill == "Intermediate") {
				window.draw(skillRookieS);
				window.draw(skillInterSelS);
				window.draw(skillVeteranS);
				window.draw(skillMasterS);
			}
			else if (aISkill == "Veteran") {
				window.draw(skillRookieS);
				window.draw(skillInterS);
				window.draw(skillVeteranSelS);
				window.draw(skillMasterS);
			}
			else {
				window.draw(skillRookieS);
				window.draw(skillInterS);
				window.draw(skillVeteranS);
				window.draw(skillMasterSelS);
			}
		}
		

		window.display();

		window.popGLStates();		
	}

	return 0;
}