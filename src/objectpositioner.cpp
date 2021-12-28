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
	float minSpeed = 0.01f;
	float speed = minSpeed;	// Store the return value
	float base = 10.0f;
	while(v >= minSpeed*base) { // This while loop keeps dividing v to find amount of digits
		v = v / base;
		speed = speed*base;	// This ensures speed will never be greater than distance
	}

	if(b-a < 0)
		speed = speed*(-1);
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

bool ObjectPositioner::mouseIsOverObject(sf::Vector2f object, sf::Vector2f mouse) {
	// If mouse x is within card's x boundaries
	if(mouse.x > object.x && mouse.x < object.x+cardDimensions.x) {
		if(mouse.y > object.y && mouse.y < object.y+cardDimensions.y) {
			return true;
		}
	}
	return false;
}

void ObjectPositioner::compressStack(std::vector<Card> &cards,
			std::vector<int> &stack, float &maxStackHeight, float &stackOffsetY) {

	int flipped = 0; // Store amount of flipped cards while compressing them first
	float startY = cards[stack[0]].getDrawable().getPosition().y;
	float endY = cards[stack.back()].getDrawable().getPosition().y;
	float flipEndY = startY;
	float stackHeight = endY+cardDimensions.y-startY;
	float oldOffset = cards[stack[1]].getDrawable().getPosition().y-startY; // Initial old offset
	float flippedOffset = 0.0f;
	float newOffset = (maxStackHeight-cardDimensions.y)/stack.size(); // Default
	float minOffset = 2.0f;
	bool compressFlipped = false; // Initial assumption is there are no flipped cards

	// Find the amount of flipped cards
	for(int i = 0; i < stack.size(); i++)
		if(cards[stack[i]].isFlipped())
			flipped++;

	if(flipped > 1) { // If stack contains more than just 1 flipped cards
		flippedOffset = (maxStackHeight-cardDimensions.y-stackOffsetY*(stack.size()-flipped))/flipped;
		flipEndY = cards[stack[flipped-1]].getDrawable().getPosition().y+flippedOffset;
		// Find new offset
		if(flippedOffset > minOffset) { // If flipped part of stack has greater offset than minimum
			compressFlipped = true; // Flipped can be compressed further
			newOffset = flippedOffset;
		} else {
			compressFlipped = false; // Must compress the nonflipped cards instead to make room
			if(stack.size() > flipped+1) { // If there are more than 1 unflipped card
				float next = cards[stack[flipped+1]].getDrawable().getPosition().y;
				oldOffset = next-cards[stack[flipped]].getDrawable().getPosition().y;
			} else {
				oldOffset = stackOffsetY; // Otherwise it can just be default
			}
			newOffset = (maxStackHeight-cardDimensions.y-(flipEndY-startY))/(stack.size()-flipped);
		}
	}

	if(newOffset < minOffset)
		newOffset = minOffset;
	else if (newOffset > stackOffsetY)
		newOffset = stackOffsetY;

	// If either stack is taller than allowed stack height or shorter and offset could be greater
	if((stackHeight-maxStackHeight >= 0.0f) ||
				(maxStackHeight > stackHeight && (newOffset-oldOffset) > 0.01f)) {
		std::cout << newOffset << " old: " << oldOffset <<
						" maxStackY: " << maxStackHeight << " stackY: " << stackHeight << std::endl;

		// Start compressing unflipped or unflipped cards
		for(int i = 1; i < stack.size(); i++) { // For all cards that are not the base card
			bool isFlipped = cards[stack[i]].isFlipped();
	 		sf::Vector2f curPos = cards[stack[i]].getDrawable().getPosition();
	 		if(isFlipped && compressFlipped) {  // If flipped are being compressed
				curPos.y = startY+i*newOffset; // Compress flipped cards from start
			} else if (compressFlipped && !isFlipped) {
	 			// Move these cards up with the compressed flipped car
				flipEndY = cards[stack[flipped-1]].getDrawable().getPosition().y+flippedOffset;
				curPos.y = flipEndY+(i-flipped)*stackOffsetY;
			} else if (!compressFlipped && !isFlipped) { // If unflipped are being compressed
				if(flipped == 1) {
					curPos.y = flipEndY+(i)*newOffset;
				} else {
					curPos.y = flipEndY+(i-flipped)*newOffset; // Start from the end of flipped part
				}
			}
			cards[stack[i]].updatePosition(curPos);
	 	}
	}
}
