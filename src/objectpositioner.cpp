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

void ObjectPositioner::createCards(int suits, sf::Vector2f xy, sf::Color cardCol, sf::Text t, const std::vector<sf::Texture>& texs) {
	int size = suits*13;				// Calculate size for vector
	cards.reserve(size);				// Allocate size in vector
	sf::Sprite sprite;					// Sprite for card
	for(int i = 1; i <= suits; i++) {		// For every suite
		sprite.setTexture(texs[i-1]); 		// Set the proper image
		for(int a = 1; a <= 13; a++) {				// For every card in a suit
			cards.push_back(Card(cardCol, a, i, xy, cardDimensions, t, sprite)); // Add to vector
		}
	}
}

std::vector<Card>& ObjectPositioner::getCards() {
	std::vector<Card>& c = cards;
	return c;
}

std::vector<sf::RectangleShape> ObjectPositioner::getCardSlotPositions() {
	return cardSlots;
}

float ObjectPositioner::adjustPositioningSpeed(const float& a, const float& b) {
	float v = (b > a) ? b-a : a-b; // First get the distance between object and destination
	float minSpeed = 50.0f;
	float speed = minSpeed;	// Store the return value
	if(v > minSpeed && !skip) { // If distance is more than min speed and animations aren't skipped
		speed = v/2;
	} else { // If speed is under minimum speed
		speed = v; // Then simply move the whole distance in next frame
	}
	if(b-a < 0) {
		speed = speed*(-1);
	}
	return speed;	// Return the optimal positioning speed
}

void ObjectPositioner::getNextCardPos(sf::Vector2f &cardPos, sf::Vector2f &destPos) {
	float speed = 0.0f; // Speed will determine how much the card moves in this frame
	if(std::abs(cardPos.x-destPos.x) >= 0.01f) {
		speed = adjustPositioningSpeed(cardPos.x, destPos.x); // Get animation speed
		cardPos.x = cardPos.x+speed; // Move horizontally towards destination
	}

	if(std::abs(cardPos.y-destPos.y) >= 0.01f) {
		speed = adjustPositioningSpeed(cardPos.y, destPos.y);
		cardPos.y = cardPos.y+speed; // Move vertically towards destination
	}
}

bool ObjectPositioner::moveCard(Card &card, sf::Vector2f destPos,	sf::Vector2f offSet, int stack) {
	sf::Vector2f cardPos = card.getDrawable().getPosition();
	destPos.x = destPos.x+stack*offSet.x; // This helps to visualize a stack
	destPos.y = destPos.y+stack*offSet.y;

	if (std::abs(cardPos.x-destPos.x) > 0.01f || std::abs(cardPos.y-destPos.y) > 0.01f) {
		getNextCardPos(cardPos, destPos); // How much card will move
		card.updatePosition(cardPos); // Update coords of object
		return true; // Card was moved successfully
	}
	return false; // Card could not be moved any more
}

bool ObjectPositioner::findMovableCard(std::vector<std::vector<int>> &stacks,
			int &moves) {
	bool cardFound = false; // Flag this if a placeable card is found
	int stack = 0; // Store stacksize of destination her
	sf::Vector2f dPos; // Store destination position here
	sf::Vector2f offSet(0.1f, -0.1f);

	for(int i = 1; i < 13; i++) { // For all top cards in lower stacks
		if(i == 1 || i >= 6) { // If stack is either dealt cards or one of the lower stacks
			if(!stacks[i].empty()) {	// If current stack is not empty
				Card& cCard = cards[stacks[i].back()];
				for(int a = 2; a < 6; a++) { // For all upper stacks
					if(!stacks[a].empty()) { // If destination is not empty
						Card& dCard = cards[stacks[a].back()]; // Get top card of the stack
						if(cCard.getSuit() == dCard.getSuit() && cCard.getNumber() == dCard.getNumber()+1) {
							cardFound = true; // A fitting card was found
							dPos = dCard.getDrawable().getPosition();
							stack = stacks[a].size();
							// If the card cant move closer to destination slot
							if(!moveCard(cards[stacks[i].back()], dPos, offSet, stack)) {
								// Save move to movehistory
								pushToHistory(std::vector<int>{stacks[i].back()}, i, a);
								// Move card reference to the new orderStack vector
								popFromAndPushTo(stacks[i], stacks[a], stacks[i].back());
								moves++;
							}
							break;
						}
					} else { // If destination is empty
						if(cCard.getNumber() == 1) { // If current card is an ace
							cardFound = true; // A fitting card was found
							dPos = cardSlots[a].getPosition();
							// If the card cant move closer to destination slot
							if(!moveCard(cards[stacks[i].back()], dPos, offSet, stack)) {
								// Save move to movehistory
								pushToHistory(std::vector<int>{stacks[i].back()}, i, a);
								// Move card reference to the new orderStack vector
								popFromAndPushTo(stacks[i], stacks[a], stacks[i].back());
								moves++;
							}
							break;
						}
					}
				}
			}
		}
	}
	return cardFound;
}

void ObjectPositioner::highLightText(sf::Text &text, sf::Vector2f &mouseCoords, bool center) {
	sf::FloatRect bounds = text.getLocalBounds();
	sf::Vector2f pos = text.getPosition();
	sf::Vector2f size = sf::Vector2f(bounds.left+bounds.width, bounds.top+bounds.height);
	if(center) { // If the text was centered
		pos.x = pos.x-size.x/2;
		pos.y = pos.y-size.y/2;
	}
	if(mouseIsOverObject(pos, size, mouseCoords)) {
		text.setFillColor(sf::Color::Yellow);
	}	else {
		text.setFillColor(sf::Color::White);
	}
}

void ObjectPositioner::highLightCard(std::vector<std::vector<int>> &stacks,
			std::pair<int, int> &select, sf::Vector2f &mouseCoords) {
	bool cardFound = false;
	for(int i = 0; i < stacks.size(); i++) { // For every stack
		if(!stacks[i].empty()) { // If that stack contains card references
			for(int a = stacks[i].size()-1; a >= 0; a--) {
				sf::RectangleShape last = cards[stacks[i][a]].getDrawable();
				// If mouse detects a card under it and no card has been detected yet
				if(mouseIsOverObject(last.getPosition(), last.getSize(), mouseCoords) && !cardFound) {
					select.first = i; // Store the highlighted card's stack's index
					select.second = stacks[i][a]; // Store the highlighted card index
					cards[stacks[i][a]].updateOutline(sf::Color::Yellow); // Highlight card
					cardFound = true; // Tell program card has been found
				}	else { // TODO set all colors in game to a vector in start of program
					if(cards[stacks[i][a]].hasOutline(sf::Color::Yellow)) { // If highlighted
						cards[stacks[i][a]].updateOutline(sf::Color::Black);	// Unhighlight
					}
				}
			}
		}
	}
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

void ObjectPositioner::updateStacks(std::vector<std::vector<int>> &stacks, float &maxStackHeight,
			float &stackOffsetY) {
	for(int i = 0; i < stacks.size(); i++) { // For every stack
		if (!stacks[i].empty()) { // If the stack has cards
			if (i == 0) { // If the stack is deck
				for (int a = 0; a < stacks[i].size(); a++) // For every card in deck
					if (!cards[stacks[i][a]].isFlipped()) // If the card isn't flipped
						cards[stacks[i][a]].setFlipped(true); // Flip the card
			} else { // If the stack is any other stack
				if (cards[stacks[i].back()].isFlipped()) { // If the top card is flipped
					if(stacks.back().empty()) // If there are no cards currently active
						cards[stacks[i].back()].setFlipped(false); // Unflip the card
				}
				// Check if stack height needs to be compressed or can be decompressed
				if(stacks.back().empty() && i > 5 && stacks[i].size() > 1) {
					compressStack(stacks[i], maxStackHeight, stackOffsetY);
				}
			}
		}
	}
}

void ObjectPositioner::pickUpStack(std::vector<std::vector<int>> &stacks, std::pair<int, int>
			&select, int &prevStack, sf::Vector2f &mouseCoords, float &stackOffsetY) {
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

void ObjectPositioner::setSkip(bool state) {
	skip = state;
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
void ObjectPositioner::compressStack(std::vector<int> &stack, float &max, float &stackOffsetY) {
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
			if(highLighted && i == highLight+1) {
				curPos.y = curPos.y + (stackOffsetY-newOffset);
			}
			cards[stack[i]].updatePosition(curPos);
		}
	} else { // Otherwise the stack height needs no adjustments
		return; // Exit function
	}
}

void ObjectPositioner::setMoves(int n) {
	moves = n;
}

int ObjectPositioner::getMoves() {
	return moves;
}

bool ObjectPositioner::undoMove(std::vector<std::vector<int>> &stacks) {
	if(!moveHistory.empty()) { // If there are moves to undo in history
		// Take the latest move from the history
		std::pair<std::vector<int>, std::pair<int, int>>& latest = moveHistory.back();
		std::cout << "last node size: " << latest.first.size() << std::endl;
		if (!latest.first.empty()) { // If there are still cards in the move
			// Move the bottom card in the stack back to it's original stack
			int index = latest.first[0]; // Bottom card of the stack
			int origStack = latest.second.first;
			int curStack = latest.second.second;
			sf::Vector2f dPos = cardSlots[std::abs(origStack)].getPosition();
			int stack = (stacks[origStack].empty()) ? 0 : stacks[origStack].size();
			sf::Vector2f offSet(0.0f, 0.0f);
			if(origStack == -1) { // If the card is actually moving back from the deck
				index = latest.first.back();
			}
			if(origStack > 5) {
				offSet.y = 25.0f;
			}

			if(!moveCard(cards[index], dPos, offSet, stack)) {
				// Card has moved to it's destination
				if(curStack == 0) {
					stacks[0].pop_back();
					stacks[1].push_back(index);
					latest.first.pop_back();
					std::cout << "Undoing deck" << std::endl;
				} else {
					int stackInd = (stacks[curStack].size()-1)-(latest.first.size()-1);
					std::cout << stacks[curStack][stackInd] << " <- card ind in curstack " << std::endl;
					std::cout << "Curstack size: " << stacks[curStack].size() <<
								 "moveStack size: " << latest.first.size() << std::endl;

					stacks[curStack].erase(stacks[curStack].begin()+stackInd);
					latest.first.erase(latest.first.begin());
					stacks[origStack].push_back(index);
				}
			}
			if(!latest.first.empty()) {
				std::cout << "There are still cards to undo in the move" << std::endl;
				return true;
			} else {
				moveHistory.pop_back(); // pop it off the history if it's empty
				return false;
			}
		}
	}
	return false; // Let the main program know there are no more cards in stack
}

void ObjectPositioner::pushToHistory(std::vector<int> cards, int from, int to) {
	std::pair<std::vector<int>, std::pair<int, int>> newMove; // Construct a move for history
	newMove.first = cards;
	newMove.second.first = from;
	newMove.second.second = to;
	moveHistory.push_back(newMove);
	std::cout << "From: " << from << " to: " << to << " these cards: ";
	for(int i = 0; i < cards.size(); i++) {
		std::cout << cards[i] << " ";
	}
	std::cout << std::endl;
}

void ObjectPositioner::clearHistory() {
	moveHistory.clear();
}
