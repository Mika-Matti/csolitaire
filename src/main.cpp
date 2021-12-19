#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "objectpositioner.hpp"
#include "card.hpp"

int main() {
	//Window settings TODO move these to their own settings file to read from
	int wWidth = 960, wHeight = 540; //Window dimensions
	sf::Color bgColor = sf::Color::Black; //Window background color

	//Card Settings
	sf::Vector2f cardDimensions = sf::Vector2f(100.0f, 150.0f);
	sf::Vector2f pos; //initial card position
	sf::Color cardColor = sf::Color::White; //Card background color
	int suits = 4;
	
	//Game elements
	std::vector<sf::RectangleShape> cardSlots;
	std::vector<Card> cards;
	int gameState = 0;
	int index = 0; //Used for animating card movement in game;

	//Initiate window and object positioner
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "CSolitaire"); //Game window
	ObjectPositioner objectPositioner(bgColor, cardDimensions); //Controls objects on window

	//Read positions for card slots from file
	objectPositioner.positionCardSlots("slotpositions.cfg"); //Set card slot positions (x,y)
	cardSlots = objectPositioner.getCardSlotPositions(); //Get and store the drawable slots

	//Create standard 52-card set in objectpositioner
	pos = cardSlots[0].getPosition();
	cards = objectPositioner.createCards(suits, pos, cardColor); //Objectpositioner creates card deck

	//Start mainloop
	while (window.isOpen()) {
		//Closing mechanism to exit mainloop	
		sf::Event event;
		while (window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}
		//Game logic and states
		
		//Redraw window
		window.clear(bgColor); //Clear the window
		//Draw the objects on the window		
		for(int i=0; i < cardSlots.size(); i++) {		
			window.draw(cardSlots[i]);	//Draw the slots where cards can be placed
		}
		//Draw card rectangles
		for(int i=0; i < cards.size(); i++) {
			window.draw(cards[i].getDrawable()); //Draw the cards with their current coords
		}
		//End drawing
		window.display(); //Update the window
	}

	return 0;
}
