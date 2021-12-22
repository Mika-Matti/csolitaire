// Copyright 2021 Mika-Matti Auerkallio

#include <iostream>
#include <string>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "objectpositioner.hpp"
#include "card.hpp"

namespace fs = std::filesystem;

int main() {
	// Window settings TODO move these to their own settings file to read from
	int wWidth = 960, wHeight = 540; // Window dimensions
	sf::Color bgColor = sf::Color::Black; // Window background color
	sf::Font font; // Font used in cards
	font.loadFromFile("fonts/Px437_IBM_VGA_8x16.ttf");

	// Card Settings
	sf::Vector2f cardDimensions = sf::Vector2f(100.0f, 150.0f);
	sf::Vector2f pos(-100.0f, -100.0f); // initial card position
	sf::Color cardColor = sf::Color::White; // Card background color
	sf::Text text("VALUE", font); // Initial text for cards
	int suits = 4;

	// Game elements
	std::vector<sf::RectangleShape> cardSlots;
	std::vector<Card> cards;
	int gameState = 0;
	int index = 0; // Used for animating card movement in game;
	sf::Vector2f cardPos(20.0f, 20.0f); // Used to track one card position
	sf::Vector2f destPos(20.0f, 20.0f);	// Used to track destination of that one card
	float offSet = 1.0f; // How much the card moves in animation;

	// Load graphic resources to a vector and pass it as a reference to functions that use it
	std::vector<sf::Texture> textures;	// Vector for storing image
	for (const auto & entry : fs::directory_iterator("textures/")) {
		std::string file = entry.path().string();
		sf::Texture tex; // Create texture object
		tex.loadFromFile(file); // Load image to texture
		textures.push_back(tex);
	}

	// Initiate window and object positioner
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "CSolitaire"); // Game window
	window.setFramerateLimit(144);
	ObjectPositioner objectPositioner(bgColor, cardDimensions); // Controls objects on window

	// Read positions for card slots from file
	objectPositioner.positionCardSlots("slotpositions.cfg"); // Set card slot positions (x,y)
	cardSlots = objectPositioner.getCardSlotPositions(); // Get and store the drawable slots

	// Create standard 52-card set in objectpositioner
	cards = objectPositioner.createCards(suits, pos, cardColor, text, textures);

	// Start mainloop
	while (window.isOpen()) {	// Closing mechanism to exit mainloop
		sf::Event event;
		while (window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// Game logic and states
		switch(gameState) {
			case 0: // Animate cards to go in place in this state
				if(index < cards.size()) {
					cardPos = cards[index].getDrawable().getPosition();
					destPos = cardSlots[0].getPosition();
					destPos.x = destPos.x+index*0.1f; // This helps to visualize a stack
					destPos.y = destPos.y-index*0.1f; // and to help game logic to see order of cards

					if(cardPos.x < destPos.x || cardPos.y < destPos.y) {
						if(cardPos.x < destPos.x) {
							offSet = objectPositioner.adjustPositioningSpeed(cardPos.x, destPos.x);
							cardPos.x = cardPos.x+offSet; // Move horizontally towards destination
						}
						if(cardPos.y < destPos.y) {
							offSet = objectPositioner.adjustPositioningSpeed(cardPos.y, destPos.y);
							cardPos.y = cardPos.y+offSet; // Move vertically towards destination
						}
						cards[index].updatePosition(cardPos); // Update coords of object
					} else {
						index++;
					}
				} else { // All cards are now in stack
					gameState++; // Progress to gamestate 1
					index = 0; // Reset index
				}
				break;
			case 1:
				// TODO Call shuffle method
				// TODO Deal cards to right slots
				break;
			default: // In any other situation
				gameState = 0; // Reset game
				break;
		}
		// End game logic

		// Redraw window
		window.clear(bgColor); // Clear the window

		// Draw the objects on the window
		for(int i = 0; i < cardSlots.size(); i++) {
			window.draw(cardSlots[i]);	// Draw the slots where cards can be placed
		}
		// Draw cards
		for(int i = 0; i < cards.size(); i++) {
			window.draw(cards[i].getDrawable());	// Draw the card rectangle
			window.draw(cards[i].getText());	// Draw the number of card
			window.draw(cards[i].getSymbol());	// Draw suit symbol of card
		}
		// End drawing
		window.display(); // Update the window
	}
	// End mainloop
	return 0;
}
