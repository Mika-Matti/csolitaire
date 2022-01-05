// Copyright 2021 Mika-Matti Auerkallio

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "objectpositioner.hpp"
#include "card.hpp"
#include "gamefunctions.hpp"
#include "popup.hpp"

namespace fs = std::filesystem;

int main() {
	// Window settings TODO move these to their own settings file to read from
	int wWidth = 960, wHeight = 540; // Window dimensions
	sf::Color bgColor = sf::Color::Black; // Window background color
	sf::Font font; // Font used in cards
	font.loadFromFile("fonts/Px437_IBM_VGA_8x16.ttf");
	unsigned int characterSizeUsed = 24;
  sf::Texture& texture = const_cast<sf::Texture&>(font.getTexture(characterSizeUsed));
  texture.setSmooth(false);

	// Card Settings
	sf::Vector2f cardDimensions = sf::Vector2f(100.0f, 150.0f);
	sf::Vector2f initPos(-100.0f, -150.0f); // Initial card position
	sf::Color cardColor = sf::Color::White; // Card background color
	sf::Text text("VALUE", font); // Initial text for cards
	text.setCharacterSize(characterSizeUsed);
	sf::Sprite cardBack, cardFront; // Depending on drawn side, either sprite is drawn for card
	float stackOffsetY = 30.0f; // When cards are stacked vertically in the lower level
	float maxStackHeight = 7; // Compress cards if stack gets higher
	int suits = 4;
	bool needShuffle = true; // If the deck has to be shuffled

	// Initiate window and object positioner
	ObjectPositioner objectPositioner(bgColor, cardDimensions); // Controls objects on window
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "CSolitaire"); // Game window
	window.setVerticalSyncEnabled(true); // Synchronize refresh rate to monitor vertical frequency

	// Game elements
	sf::Text coords = text; // Display this text in upper right corner of window
	coords.setPosition(wWidth-100, wHeight-30);
	sf::Text seedText = text; // Display the seed of the current game
	seedText.setPosition(5, wHeight-30);
	sf::Text newGameText = text; // Text element for newGameBtn
	newGameText.setPosition(wWidth-105, 10);
	newGameText.setString("NEW GAME");

	sf::RectangleShape popupShape = objectPositioner.createRectangle(sf::Vector2f(400, 200),
				sf::Vector2f(wWidth/2-200, wHeight/2-100), sf::Color::Red, sf::Color::Black, 5);
	sf::Text newGameTitle = text;
	newGameTitle.setString("START NEW GAME");
	Popup newGamePopup(popupShape, newGameTitle);	// New game popup window

	sf::Vector2f mouseCoords; // For storing mouse coordinates
	std::vector<sf::RectangleShape> cardSlots;
	std::vector<Card> cards;
	std::vector<std::vector<int>> orderStacks; // Holds reference to cards in stack and depth order
	bool animating = false; // Control animating card movement during gameplay
	bool rightClicked = false; // If mouse was right clicked, program finds cards it can place up
	bool newGameConfirm = false; // Flagged true if new game is confirmed from popup window
	bool stackChanged = false; // Call the compression function if this is true
	int gameState = 0; // Used to control the phases of the game
	int index = 0; // Used to select card for animating movement in game
	int amount = 1; // How many cards will be dealt to this slot
	int closestStack = 0; // Used for animating card stacks moving to closest stack
	int prevStack = 0; // For checking what stack the card came from
	int64_t seed = 0; // Seed used to generate the shuffled card deck for the game
	std::pair <int, int> highLighted(0, 0); // Points to a stack and card that is highlighted
	sf::Vector2f cardPos(20.0f, 20.0f); // Used to track one card position
	sf::Vector2f destPos(20.0f, 20.0f);	// Used to track destination of that one card

	// Load graphic resources to a vector and pass it as a reference to functions that use it
	std::vector<sf::Texture> textures;	// Vector for storing image
	for (const auto & entry : fs::directory_iterator("textures/")) {
		std::string file = entry.path().string();
		sf::Texture tex; // Create texture object
		tex.loadFromFile(file); // Load image to texture
		textures.push_back(tex);
	}
	cardBack.setTexture(textures[4]); // Add texture to card back
	cardFront.setTexture(textures[5]); // Add texture to card front

	// Read positions for card slots from file
	objectPositioner.positionCardSlots("slotpositions.cfg"); // Set card slot positions (x,y)
	cardSlots = objectPositioner.getCardSlotPositions(); // Get and store the drawable slots
	// Initiate orderStacks vector with cardSlots length
	for(int i = 0; i < cardSlots.size()+1; i++) { // For every card slot + stack moved by mouse
		std::vector<int> v; // Initiate a stack for card index references
		orderStacks.push_back(v); // Push it to the order of stacks
	}

	// Create standard 52-card set in objectpositioner
	cards = objectPositioner.createCards(suits, initPos, cardColor, text, textures);

	// Start mainloop
	while (window.isOpen()) {	// Mechanism to exit
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		} // Exit mechanism ends

		coords.setString(updateMouseCoords(mouseCoords, window)); // Set text to new mouse coords

		// Game logic and states
		switch(gameState) {
			case 0: // Shuffle deck and animate cards to go in place in this state
				if(needShuffle) {
					resetDrawOrder(orderStacks, cards);
					seed = std::time(0); // Set seed for new shuffle
					seedText.setString("SEED:" + std::to_string(seed)); // Set the new seed for display
					std::srand(seed); // Set the seed for the deck shuffling
					std::random_shuffle(cards.begin(), cards.end()); // Perform the shuffling of deck
					needShuffle = false;
				}

				// Begin animating card movement to default slot
				if(index < cards.size()) {	// Move cards one by one towards their destination
					if(!objectPositioner.moveCard(cards[index], cardSlots[0].getPosition(),
								sf::Vector2f(0.1f, -0.1f), index)) { // If card can not be moved anymore
						index++; // Move to the next card
					}
				} else { // All cards are now in stack
					gameState++; // Progress to gamestate 1
					index = cards.size()-1; // Set card index for next state
				}
				break;
			case 1:
				// Deal cards from stack to stacks where stack n (n = amount) has n(n+n)/2 cards
				if(amount <= 7) {
					int ind = 6+amount-1; // Index of card destination stack
					popFromAndPushTo(orderStacks[0], orderStacks[ind], index); // Update draw order
					// Move card towards it's destination if possible
					if(!objectPositioner.moveCard(cards[index], cardSlots[ind].getPosition(),
								sf::Vector2f(0.0f, stackOffsetY), orderStacks[ind].size()-1)) {
						index--; // Otherwise move to next card
						if(amount == orderStacks[ind].size()) // If this slot has had it's cards dealt
							amount++; // Increase amount of cards allowed in stack
					}
				} else { // The game is set for playing
					gameState++; // Progress to game state 2
					index = 0; // Reset card index for when game is won or new game is selected
					amount = 1; // Reset amount of cards to deal to current slot
					stackChanged = true;
				}
				break;
			case 2: // The gameplay state and mouse events
				// Check for cards that can be flipped or for stacks that need vertical compression
				if(stackChanged && !animating && !rightClicked) {
					updateStacks(cards, orderStacks, objectPositioner, maxStackHeight, stackOffsetY);
					stackChanged = false; // Stack changes have been processed
				}

				// Game controls
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // If mouse left button is pressed
					// If user is clicking on a highlighted card and the move is allowed
					if(moveIsLegal(cards, orderStacks[highLighted.first], highLighted)) {
						objectPositioner.pickUpStack(cards, orderStacks, highLighted, prevStack, mouseCoords,
								stackOffsetY); // Pick up that card/cards
					} else if (areSameColor(newGameText.getFillColor(), sf::Color::Yellow)) {
						// New game was clicked
						newGamePopup.setVisibility(true); // Open new game popup window
						newGameText.setFillColor(sf::Color::White); // Unhighlight button
					} else if (newGamePopup.getVisibility()) { // If new game popup is open
						if(newGamePopup.clickedButton(0)) { // If clicked new game
							newGameConfirm = true; // Confirm new game selection
							newGamePopup.setVisibility(false); // Close window
						}	else if (newGamePopup.clickedButton(newGamePopup.getTexts().size()-1)) {
							newGamePopup.setVisibility(false); // Clicked close window
						}
					} else { // If deck is clicked
						sf::RectangleShape deck = cardSlots[0];
						if(objectPositioner.mouseIsOverObject(deck.getPosition(), deck.getSize(),
									mouseCoords) && orderStacks[0].empty() && orderStacks.back().empty()) {
							// Empty deck was clicked. Move the whole stack 1 to active stack
							while(!orderStacks[1].empty()) {
								orderStacks.back().push_back(orderStacks[1].back()); // Push new on top
								orderStacks[1].pop_back(); // Remove top from old stack
							}
							prevStack = -1; // Setting this to -1 will restore dealt cards to deck
						}
					}
				} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) { // If mouse right is pressed
					if(rightClicked == false)
						rightClicked = true;
				} else { // If mouse is not pressed
					// If there are cards in the last stack, place them to the nearest allowed stack
					if(!orderStacks.back().empty() && !animating) { // If there are cards picked up
						// Find closest allowed card stack to put them in
						closestStack = findClosestStack(cards, cardSlots, orderStacks, prevStack, mouseCoords);
						animating = true; // Begin animation of selected cards moving to closest stack
					} else if (animating) { // Animate card closing to their destination position
						stackChanged = true; // A change is happening in the stacks
						int stack = orderStacks[closestStack].size();
						sf::Vector2f dest = cardSlots[closestStack].getPosition(); // Destination for cards
						sf::Vector2f offSet(0.1f, -0.1f);
						if(closestStack > 5) {
							offSet.x = 0.0f;
							offSet.y = stackOffsetY;
						}
						// If the card cant move closer to destination slot
						if(!objectPositioner.moveCard(cards[orderStacks.back()[0]], dest, offSet, stack)) {
							// Move card reference to the new orderStack vector
							orderStacks[closestStack].push_back(orderStacks.back()[0]); // Place to the new
							orderStacks.back().erase(orderStacks.back().begin()); // Erase from old stack
							if(orderStacks.back().empty()) // If there are no cards left
								animating = false;
						}
					} else if (rightClicked) { // Find all cards that can be placed to upper stacks
						if(!findMovableCard(cards, cardSlots, orderStacks, objectPositioner)) {
							rightClicked = false; // All movable cards have been found
						} else {
							stackChanged = true;
						}
					} else {
						// If mouse is over an object, highlight it
						if(newGamePopup.getVisibility()) { // If popup is open
							std::vector<sf::Text>& texts = newGamePopup.getTexts();
							for(int i = 0; i < texts.size(); i++) // For every text in the window
								highLightText(texts[i], objectPositioner, mouseCoords, true);
						}	else {
							highLightText(newGameText, objectPositioner, mouseCoords, false);
							highLightCard(cards, orderStacks, highLighted, objectPositioner, mouseCoords);
						}
					}
				} // End game controls

				// Check if new game was initiated
				if(newGameConfirm) {
					newGameConfirm = false; // Unflag the newGame variable
					needShuffle = true;
					gameState = 0; // Reset game
				}
				// Check for win conditions
				if (haveWinConditions(cards, orderStacks)) { // If all conditions for winning were met
					needShuffle = true;
					rightClicked = false;
					gameState++;
				}
				break;	// Gameplay part ends
			case 3: // If the game has been won
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // If mouse is clicked
					gameState = 0; // Reset game
				break;
			default: // In any other situation
				gameState = 0; // Reset game
				break;
		}
		// End game logic

		// Redraw window
		window.clear(bgColor); // Clear the window
		// Draw the objects on the window
		window.draw(coords); // TODO add all the text objects to a vector
		window.draw(newGameText);
		window.draw(seedText);

		// Draw cardslots
		for(int i = 0; i < cardSlots.size(); i++) {
			window.draw(cardSlots[i]); // Draw the slots where cards can be placed
		}
		// Order of placement mapped to cards is used to draw the cards in right order
		for(int i = 0; i < orderStacks.size(); i++) { // For every reference stack
			for(int a = 0; a < orderStacks[i].size(); a++) { // For every reference in that stack
				window.draw(cards[orderStacks[i][a]].getDrawable());	// Draw the card rectangle
				if(cards[orderStacks[i][a]].isFlipped()) { // If card is coverside up
					cardBack.setPosition(cards[orderStacks[i][a]].getDrawable().getPosition());
					window.draw(cardBack);
				} else {
					cardFront.setPosition(cards[orderStacks[i][a]].getDrawable().getPosition());
					window.draw(cardFront); // Draw the card texture
					window.draw(cards[orderStacks[i][a]].getText());	// Draw the number of card
					window.draw(cards[orderStacks[i][a]].getSymbol());	// Draw suit symbol of card
				}
			}
		}

		if(newGamePopup.getVisibility()) { // If popup is open
			window.draw(newGamePopup.getShape()); // Display new game popup window
			std::vector<sf::Text>& texts = newGamePopup.getTexts();
			for(int i = 0; i < texts.size(); i++) // For every text in the window
				window.draw(texts[i]); // Draw the text
		}

		// End drawing
		window.display(); // Update the window
	}
	// End mainloop
	return 0;
}
