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
	sf::Vector2f pos(-100.0f, -150.0f); //initial card position
	sf::Color cardColor = sf::Color::White; //Card background color
	int suits = 4;
	
	//Game elements
	std::vector<sf::RectangleShape> cardSlots;
	std::vector<Card> cards;
	int gameState = 0;
	int index = 0; //Used for animating card movement in game;
	sf::Vector2f cardPos(20.0f, 20.0f); //Used to track one card position
	sf::Vector2f destPos(20.0f, 20.0f);	//Used to track destination of that one card
	float offSet = 10.0f; //How much the card moves in animation;

	//Initiate window and object positioner
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "CSolitaire"); //Game window
	window.setFramerateLimit(200);
	ObjectPositioner objectPositioner(bgColor, cardDimensions); //Controls objects on window

	//Read positions for card slots from file
	objectPositioner.positionCardSlots("slotpositions.cfg"); //Set card slot positions (x,y)
	cardSlots = objectPositioner.getCardSlotPositions(); //Get and store the drawable slots

	//Create standard 52-card set in objectpositioner
	//pos = cardSlots[0].getPosition();
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
		if(gameState == 0) { //Animate cards to go in place in this state
			if(index < cards.size()) {
				cardPos = cards[index].getDrawable().getPosition();
				destPos = cardSlots[0].getPosition();

				if(cardPos.x < destPos.x || cardPos.y < destPos.y) {
					if(cardPos.x < destPos.x) {
						cardPos.x = cardPos.x+offSet; //Move horizontally towards destination
					}
					if(cardPos.y < destPos.y) {
						cardPos.y = cardPos.y+offSet; //Move vertically towards destination
					}
					cards[index].updatePosition(cardPos); //Update coords of object
				} else {
					index++;
				}
			} else {
				gameState++;
				index = 0;
			}	
		}
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
