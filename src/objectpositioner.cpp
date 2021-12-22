// Copyright 2021 Mika-Matti Auerkallio

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "card.hpp"
#include "objectpositioner.hpp"

// Constructor
ObjectPositioner::ObjectPositioner(sf::Color bg, sf::Vector2f dims) {
	bgColor = bg;
	cardDimensions = dims;
}
// Destructor
ObjectPositioner::~ObjectPositioner() {
	std::cout << "Object positioner is destroyed" << std::endl;
}

// Functions
void ObjectPositioner::positionCardSlots(std::string f) {
	std::ifstream slotPositions(f); // Holds card slot positions (x,y)
	int x, y; // Store current positions of the card
	while (slotPositions >> x >> y) { // Read positions for card slots from file
		sf::RectangleShape cardSlot(cardDimensions); // Card slot with shape
		cardSlot.setOutlineColor(sf::Color::Red); // Cardslot outline color TODO change to parameter
		cardSlot.setFillColor(sf::Color::Transparent); // Cardslot has no filled color
		cardSlot.setOutlineThickness(5); // Outline thickness
		cardSlot.setPosition(x, y); // Set position
		cardSlots.push_back(cardSlot); // Add to the vector that will be drawn in mainloop
	}
}

std::vector<Card> ObjectPositioner::createCards(int suits, sf::Vector2f xy, sf::Color cardCol, sf::Text t, const std::vector<sf::Texture>& texs) {
	std::vector<Card> cards;		// Initiate vector
	int size = suits*13;				// Calculate size for vector
	cards.reserve(size);				// Allocate size in vector
	sf::Sprite sprite;					// Sprite for card
	for(int i = 1; i <= suits; i++) {		// For every suite
		sprite.setTexture(texs[i-1]); 		// Set the proper image
		for(int a = 1; a <= 13; a++) {				// For every card in a suit
			cards.push_back(Card(cardCol, a, i, xy, cardDimensions, t, sprite)); // Add to vector
		}
	}
	return cards;
}

std::vector<sf::RectangleShape> ObjectPositioner::getCardSlotPositions() {
	return cardSlots;
}

float ObjectPositioner::adjustPositioningSpeed(const float& a, const float& b) {
	float v = (b > a) ? b-a : a-b; // First get the distance between object and destination
	float minSpeed = 0.1f;
	float speed = minSpeed;	// Store the return value
	float base = 10.0f;
	while(v >= minSpeed*base) { // This while loop keeps dividing v to find amount of digits
		v = v / base;
		speed = speed*base;	// This ensures speed will never be greater than distance
	}

	if(b-a < 0)
		speed = speed*(-1);

	std::cout << "speed" << speed << std::endl;

	return speed;	// Return the optimal positioning speed
}

void ObjectPositioner::getNextCardPos(float &offSet, sf::Vector2f &cardPos, sf::Vector2f &destPos) {
	if(std::abs(cardPos.x-destPos.x) > 0.0001f) {
		offSet = adjustPositioningSpeed(cardPos.x, destPos.x);
		cardPos.x = cardPos.x+offSet; // Move horizontally towards destination
	}
	if(std::abs(cardPos.y-destPos.y) > 0.0001f) {
		offSet = adjustPositioningSpeed(cardPos.y, destPos.y);
		cardPos.y = cardPos.y+offSet; // Move vertically towards destination
	}
}

