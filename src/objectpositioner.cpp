// Copyright 2021 Mika-Matti Auerkallio

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
		// Card slot with shape
		sf::RectangleShape cardSlot = createRectangle(cardDimensions, sf::Vector2f(x, y),
					sf::Color::Red, sf::Color::Transparent, 5);
		cardSlots.push_back(cardSlot); // Add to the vector that will be drawn in mainloop
	}
}

sf::RectangleShape ObjectPositioner::createRectangle(sf::Vector2f dims, sf::Vector2f pos,
			sf::Color outLine, sf::Color fill, int edgeSize) {
	sf::RectangleShape object(dims); // Create shape with dimensions
	object.setOutlineColor(outLine); // Set outline color for the card
	object.setFillColor(fill); // Set background color for the shape
	object.setOutlineThickness(edgeSize); // Set outline thickness
	object.setPosition(pos); // Set position
	return object;
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
	float minSpeed = 150.0f;
	float speed = minSpeed;	// Store the return value
	float base = 10.0f; // Speed will be in the form n*base^x
	if(v > minSpeed) {
		while(v >= minSpeed*base) { // This while loop keeps dividing v to find amount of digits
			v = v / base;
			speed = speed*base;	// This ensures speed will never be greater than distance
		}
	} else { // If speed is under minimum speed
		speed = v; // Then simply move the whole distance in next frame
	}

	if(b-a < 0)
		speed = speed*(-1);
	return speed;	// Return the optimal positioning speed
}

void ObjectPositioner::getNextCardPos(sf::Vector2f &cardPos, sf::Vector2f &destPos) {
	float speed = 0.0f; // Speed will determine how much the card moves in this frame
	if(std::abs(cardPos.x-destPos.x) >= 0.01f) {
		speed = adjustPositioningSpeed(cardPos.x, destPos.x); // Get animation speed
		cardPos.x = cardPos.x+speed; // Move horizontally towards destination
	}

	if(std::abs(cardPos.y-destPos.y) > 0.01f) {
		speed = adjustPositioningSpeed(cardPos.y, destPos.y);
		cardPos.y = cardPos.y+speed; // Move vertically towards destination
	}
}

bool ObjectPositioner::moveCard(Card &card, sf::Vector2f destPos,	sf::Vector2f offSet, int stack) {
	sf::Vector2f cardPos = card.getDrawable().getPosition();
	destPos.x = destPos.x+stack*offSet.x; // This helps to visualize a stack
	destPos.y = destPos.y+stack*offSet.y; // and to help game logic to see order of cards

	if (std::abs(cardPos.x-destPos.x) > 0.01f || std::abs(cardPos.y-destPos.y) > 0.01f) {
		getNextCardPos(cardPos, destPos); // How much card will move
		card.updatePosition(cardPos); // Update coords of object
		return true; // Card was moved successfully
	}
	return false; // Card could not be moved any more
}

bool ObjectPositioner::mouseIsOverObject(sf::Vector2f object, sf::Vector2f size,
			sf::Vector2f mouse) {
	// If mouse x is within card's x boundaries
	if(mouse.x > object.x && mouse.x < object.x+size.x) {
		if(mouse.y > object.y && mouse.y < object.y+size.y) {
			return true;
		}
	}
	return false;
}

void ObjectPositioner::pickUpStack(std::vector<Card> &cards,
			std::vector<std::vector<int>> &stacks, std::pair<int, int> &select,
			int &prevStack, sf::Vector2f &mouseCoords, float &stackOffsetY) {
	// Move all cards on top of highlighted card to the last stack
	if (select.first != stacks.size()-1) { // If card/cards are in old stack
		int i = 0; // Iterator to find selected card's position in stack
		while(stacks[select.first][i] != select.second) {
			i++; // Skip cards till the selected card is found
		}
		while(i < stacks[select.first].size()) { // Move all after card i
			stacks.back().push_back(stacks[select.first][i]); // To this stack
			stacks[select.first].erase(stacks[select.first].begin()+i);
			// And remove card from it's old stack
		}
		prevStack = select.first; // Store old stack index
		select.first = stacks.size()-1; // Update highlight stack index
	}
	// Update card position with values converted from mouse position
	for(int i = 0; i < stacks.back().size(); i++) {
		sf::Vector2f mouseCoord = mouseCoords; // Store mousecoord
		mouseCoord.x = mouseCoord.x-cardDimensions.x/2; // Center the card to mouse
		mouseCoord.y = (mouseCoord.y-cardDimensions.y/2)+i*stackOffsetY;
		cards[stacks.back()[i]].updatePosition(mouseCoord);
	}
}

/**
 * This algorithm will take the indexes of the current stack and
 * check their length in full size in the form of equation
 * a/max + b/max = 1 Where a is the amount of flipped and b is
 * the amount of unflipped cards. If the value exceeds 1, the
 * algorithm will first calculate a compression value x for
 * flipped cards that can compress the maximum offset to 
 * any smaller size with minimum size of 2. Value x is used
 * to divide value a to find the new offset for flipped cards.
 *
 * The algorithm then checks if (a/x)/max + b/max = 1. If the
 * value is more than 1 and the value a/x is at minimum of 2,
 * The algorithm will then calculate the new compression value y
 * for unflipped cards with the same minimum size, resulting in
 * the equation (a/x)/max + (b/y)/max = 1.
 */
void ObjectPositioner::compressStack(std::vector<Card> &cards,
			std::vector<int> &stack, float &max, float &stackOffsetY) {

	int highLight = stack.size()-1; // Assume highlight is just last card
	int flipped = 0; // Store amount of flipped cards while compressing them first
	float startY = cards[stack[0]].getDrawable().getPosition().y;
	float flipEndY = startY; // Assume there is no flipped cards
	float stackHeight = 1.0f; // The proportions of the stack should add up to one
	float minOffset = 2.0f; // Limit for compression
	float flippedOffset = 1.0f; // Used for compressing flipped cards
	float newOffset = stackOffsetY; // Compress open cards
	bool highLighted = false; // If a card is highlighted, uncompress every card after that
	sf::Vector2f curPos; // Used to store current position of a card

	// Straighten the stack first and find any flipped cards and if there is a highlighted card
	for(int i = 0; i < stack.size(); i++) { // For every card in the stack
		curPos = cards[stack[i]].getDrawable().getPosition(); // Get the card position
		curPos.y = startY+i*stackOffsetY; // Revert to maximum stacksize and offset
		cards[stack[i]].updatePosition(curPos); // Update the card position
		if(cards[stack[i]].isFlipped()) { // If the card is flipped down
			flipped++;
		} else if (cards[stack[i]].hasOutline(sf::Color::Yellow)) { // If the card is highlighted
			highLighted = true; // Let program know there is a highlighted card
			highLight = i; // Index of highlight in stack
		}
	}

	// Update and stack height
	stackHeight = flipped/max+(stack.size()-flipped)/max;

	if(stackHeight > 1.0f) { // If the sum of stack proportions exceed maximum of 1
		// First compress flipped cards
		if(flipped > 0) { // If there are flipped cards
			float a = flipped, b = (stack.size()-flipped);
			float x = a/(max-b); // Formula for x is derived from (a/x)/max + b/max=1
			flippedOffset = stackOffsetY/x; // Where dividing with x gives the new offset
			if(flippedOffset < minOffset) { // In case the offset is smaller than minimum allowed
				flippedOffset = minOffset; // Replace it with minimum
			}
			for(int i = 0; i < flipped; i++) { // For every flipped card
				curPos = cards[stack[i]].getDrawable().getPosition(); // Get the card position
				curPos.y = startY+i*flippedOffset; // Update position with new offset
				cards[stack[i]].updatePosition(curPos); // Update card position
			}
			// Update the stored endpoint of flipped cards that is used to place unflipped cards
			flipEndY = curPos.y+flippedOffset;
			stackHeight = flippedOffset/max+b/max; // Update stack height
		}
		// Then check for unflipped cards
		if(stackHeight > 1.0f && flippedOffset <= minOffset) { // If the sum of proportions exceed 1
			std::cout << stackHeight << std::endl;
			// Calculate new offset for unflipped cards
			float ax = flippedOffset, b = (stack.size()-flipped);
			float y = b/(max-ax); // Formula for y is derived from (a/x)/max + (b/y)/max = 1
			newOffset = stackOffsetY/y; // Where dividing with y gives the new offset
			if(newOffset < minOffset) { // In case the offset is smaller than minimum allowed
				newOffset = minOffset; // Replace it with minimum
			}
		}

		// Move the unflipped cards up and compress them if needed
		for(int i = flipped; i < stack.size(); i++) { // For every unflipped card
			curPos = cards[stack[i]].getDrawable().getPosition();
		 	curPos.y = flipEndY+(i-flipped)*newOffset;
			cards[stack[i]].updatePosition(curPos);
		}
	} else { // Otherwise the stack height needs no adjustments
		return; // Exit function
	}
}
