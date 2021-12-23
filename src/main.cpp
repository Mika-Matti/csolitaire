// Copyright 2021 Mika-Matti Auerkallio

#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
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
	sf::Vector2f initPos(-100.0f, -150.0f); // Initial card position
	sf::Color cardColor = sf::Color::White; // Card background color
	sf::Text text("VALUE", font); // Initial text for cards
	int suits = 4;
	bool needShuffle = true; // If the deck has to be shuffled

	// Game elements
	std::vector<sf::RectangleShape> cardSlots;
	std::vector<Card> cards;
	std::vector<std::vector<int>> orderStacks; // Holds reference to cards in stack and depth order
	int gameState = 0;
	int index = 0; // Used to select card for animating movement in game
	int stack = 0; // Also used to find final position for card in movement
	int amount = 1; // How many cards will be dealt to this slot
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
	// window.setFramerateLimit(300);
	ObjectPositioner objectPositioner(bgColor, cardDimensions); // Controls objects on window

	// Read positions for card slots from file
	objectPositioner.positionCardSlots("slotpositions.cfg"); // Set card slot positions (x,y)
	cardSlots = objectPositioner.getCardSlotPositions(); // Get and store the drawable slots
	// Initiate orderStacks vector with cardSlots length
	for(int i = 0; i < cardSlots.size(); i++) { // For every card slot
		std::vector<int> v; // Initiate a stack for card index references
		orderStacks.push_back(v); // Push it to the order of stacks
	}

	// Create standard 52-card set in objectpositioner
	cards = objectPositioner.createCards(suits, initPos, cardColor, text, textures);

	// Start mainloop
	while (window.isOpen()) {	// Closing mechanism to exit mainloop
		sf::Event event;
		while (window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// Game logic and states
		switch(gameState) {
			case 0: // Shuffle deck and animate cards to go in place in this state
				if(needShuffle) {
					std::random_shuffle(cards.begin(), cards.end());
					needShuffle = false;
					// Update drawing order to the map
					for(int i = 0; i < cards.size(); i++) {
						orderStacks[0].push_back(i); // Set initial drawing order where order i has card i
					}
				}

				// Begin animating card movement to default slot
				if(index < cards.size()) {
					cardPos = cards[index].getDrawable().getPosition();
					destPos = cardSlots[0].getPosition();
					destPos.x = destPos.x+stack*0.1f; // This helps to visualize a stack
					destPos.y = destPos.y-stack*0.1f; // and to help game logic to see order of cards

				 if (std::abs(cardPos.x-destPos.x) > 0.0001f || std::abs(cardPos.y-destPos.y) > 0.0001f) {
						objectPositioner.getNextCardPos(offSet, cardPos, destPos);
						cards[index].updatePosition(cardPos); // Update coords of object
					} else {
						index++; // Move onto moving the next card
						stack++; // Increase offset for stack effect
					}
				} else { // All cards are now in stack
					gameState++; // Progress to gamestate 1
					index = cards.size()-1; // Set card index for next state
					stack = 0; // Reset stack
				}
				break;
			case 1:
				// Deal cards from stack 7 to stack 1 where stack n has n(n+n)/2 cards
				if(stack < 7 && amount <= 7) {
					cardPos = cards[index].getDrawable().getPosition();
					destPos = cardSlots[6+amount-1].getPosition();
					destPos.y = destPos.y+stack*20.0f; // Vertical stack effect for cards
					// If the card is not yet in it's destination slot
					if (std::abs(cardPos.x-destPos.x) > 0.01f || std::abs(cardPos.y-destPos.y) > 0.01f) {
							objectPositioner.getNextCardPos(offSet, cardPos, destPos);
							cards[index].updatePosition(cardPos); // Update coords of object;
					} else { // Move card reference to the new orderStack vector
						orderStacks[0].pop_back(); // Take top item from initial stack order reference vector
						orderStacks[6+amount-1].push_back(index); // Place to the new vector
						// Move onto next card and increase stack size
						index--;
						stack++;
						if(amount == stack) { // If this slot has had it's cards dealt
							stack = 0; // Reset to the empty stack size
							amount++; // Increase amount of cards allowed in stack
						}
					}
				} else { // The game is set for playing
					gameState++; // Progress to game state 2
					index = 0; // Reset card index
					stack = 0; // Reset stack
					amount = 1; // Reset amount of cards to deal to current slot
				}
				break;
			case 2:
				// The gameplay state
				// If mouse is over a selectable card
				for(int i = 0; i < orderStacks.size(); i++) { // For every stack
					if(!orderStacks[i].empty()) { // If that stack contains card references
						sf::RectangleShape last = cards[orderStacks[i].back()].getDrawable();
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);
						if(objectPositioner.mouseIsOverObject(last.getPosition(), mousePos)) {
							cards[orderStacks[i].back()].updateOutline(sf::Color::Yellow); // Highlight card
						}	else { // TODO set all colors in game to a vector in start of program
							if(last.getOutlineColor().r == sf::Color::Yellow.r &&
									 last.getOutlineColor().g == sf::Color::Yellow.g &&
									 last.getOutlineColor().b == sf::Color::Yellow.b) { // If card is highlighted
								cards[orderStacks[i].back()].updateOutline(sf::Color::Black);	// Unhighlight card
							}
						}
					}
				}
				// TODO if slot 0 is clicked, move the top card to slot 2
				// TODO if a card in any other slot than 0 is clicked, drag it along with mouse
				// TODO make the dragged card move automatically to closest slot
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
			window.draw(cardSlots[i]); // Draw the slots where cards can be placed
		}
		// Order of placement mapped to cards is used to draw the cards in right order
		for(int i = 0; i < orderStacks.size(); i++) { // For every reference stack
			for(int a = 0; a < orderStacks[i].size(); a++) { // For every reference in that stack
				window.draw(cards[orderStacks[i][a]].getDrawable());	// Draw the card rectangle
				window.draw(cards[orderStacks[i][a]].getText());	// Draw the number of card
				window.draw(cards[orderStacks[i][a]].getSymbol());	// Draw suit symbol of card
			}
		}
		// End drawing
		window.display(); // Update the window
	}
	// End mainloop
	return 0;
}
