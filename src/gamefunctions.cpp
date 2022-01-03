// Copyright 2021 Mika-Matti Auerkallio

#include "gamefunctions.hpp"

// Function definitions
bool areSameColor(sf::Color a, sf::Color b) {
	if(a.r == b.r && a.g == b.g && a.b == b.b) {
		return true;
	}
	return false;
}

void popFromAndPushTo(std::vector<int> &a, std::vector<int> &b, int &x) {
	if(a.back() == x) { // If the top item x is still in old vector a
		a.pop_back(); // Remove the top item x from the old vector a
		b.push_back(x); // Push to the new vector b
	}
}

void updateStacks(std::vector<Card> &cards, std::vector<std::vector<int>> &stacks,
			ObjectPositioner &op, float &maxStackHeight, float &stackOffsetY) {

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
					op.compressStack(cards, stacks[i],	maxStackHeight, stackOffsetY);
				}
			}
		}
	}
}

void resetDrawOrder(std::vector<std::vector<int>> &stacks, std::vector<Card> &cards) {
	// Make sure every stack in orderStacks is empty
	for(int i = 0; i < stacks.size(); i++) { // For every stack
		if(!stacks[i].empty()) // If that stack is not empty
			stacks[i].clear(); // Clear it
	}
	// Update drawing order
	for(int i = 0; i < cards.size(); i++) {
		if(!cards[i].isFlipped()) // If this card is not flipped
			cards[i].setFlipped(true); // Flip the card to face downside
		stacks[0].push_back(i); // Set initial drawing order where order i has card i
	}
}

std::string updateMouseCoords(sf::Vector2f &mouseCoords, sf::RenderWindow &window) {
	std::string coords = "";
	mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	std::string x = std::to_string(mouseCoords.x);
	std::string y = std::to_string(mouseCoords.y);
	coords = x.substr(0, x.find(".")) + ", "	+ y.substr(0, y.find("."));
	return coords;
}

void highLightText(sf::Text &text, ObjectPositioner &op, sf::Vector2f &mouseCoords) {
	sf::FloatRect bounds = text.getLocalBounds();
	sf::Vector2f size = sf::Vector2f(bounds.left+bounds.width, bounds.top+bounds.height);

	if(op.mouseIsOverObject(text.getPosition(), size, mouseCoords)) {
		text.setFillColor(sf::Color::Yellow);
	}	else {
		text.setFillColor(sf::Color::White);
	}
}

void highLightCard(std::vector<Card> &cards, std::vector<std::vector<int>> &stacks,
			std::pair<int, int> &select, ObjectPositioner &op, sf::Vector2f &mouseCoords) {
	bool cardFound = false;
	for(int i = 0; i < stacks.size(); i++) { // For every stack
		if(!stacks[i].empty()) { // If that stack contains card references
			for(int a = stacks[i].size()-1; a >= 0; a--) {
				sf::RectangleShape last = cards[stacks[i][a]].getDrawable();
				// If mouse detects a card under it and no card has been detected yet
				if(op.mouseIsOverObject(last.getPosition(), last.getSize(), mouseCoords) &&	!cardFound) {
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

bool moveIsLegal(std::vector<Card> &cards, std::vector<int> &stack, std::pair<int, int> &select) {
	// If the selected card is not flipped
	if(cards[select.second].hasOutline(sf::Color::Yellow) &&
			(select.first == 0 && cards[select.second].isFlipped() ||
			select.first > 0 && !cards[select.second].isFlipped())) {
		if(select.second != stack.back()) { // If the selected is not the top card
			// If the stack from selected to last card is descending and color varies on every card
			int ind = 999;
			int prevNumber = -1;
			sf::Color prevCol;
			for(int i = 0; i < stack.size(); i++) {
				if(stack[i] == select.second) { // If the select card from stack is found
					ind = i;
					prevNumber = cards[stack[i]].getNumber(); // Store the number of the card
					prevCol = cards[stack[i]].getText().getFillColor(); // Store the color of the card
				} else if (i > ind) { // If card comes after select card
					int thisNumber = cards[stack[i]].getNumber();
					sf::Color thisCol = cards[stack[i]].getText().getFillColor();
					if(thisNumber != prevNumber-1 || areSameColor(prevCol, thisCol)) {
						return false;
					} else {
						prevNumber = thisNumber;
						prevCol = thisCol;
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool haveWinConditions(std::vector<Card> &cards, std::vector<std::vector<int>> &stacks) {
	for(int i = 2; i < 6; i++) { // For every slot in upper right area of window
		if(stacks[i].size() != 13) // If stack is not the complete size
			return false; // Stop going through cards
		int cSuit = 0; // This is used to check that the stack only has same suit cards
		for(int a = 0; a < stacks[i].size(); a++) { // For every card in the stack
			if(a == 0) // If we are at the first card of the stack
				cSuit = cards[stacks[i][a]].getSuit(); // Set the suit of the stack
			if(cards[stacks[i][a]].getSuit() != cSuit) // If card don't have right suit
				return false;
			if(cards[stacks[i][a]].getNumber() != a+1) // If card number is not a+1
				return false;
		}
	} // End checking win conditions
	return true;
}

int findClosestStack(std::vector<Card> &cards, std::vector<sf::RectangleShape> &slots,
			std::vector<std::vector<int>> &stacks, int &prevStack, sf::Vector2f &m) {
	float shortestDistance = 9999999.0f;
	float closestStack = prevStack; // Result that will be returned from function
	if(prevStack == 0) { // If the stack is the deck
		closestStack = 1; // Then the cards go to the stack next to deck
	} else if (prevStack == -1) { // If the deck is empty
		closestStack = 0; // Cards dealt to slot next to deck return to deck
	} else {	// In all other cases, find a stack closest to the cards held by mouse
		for(int i = 1; i < slots.size(); i++) { // Skipping first slot
			sf::Vector2f dims = slots[i].getSize();
			int	sx = slots[i].getPosition().x+dims.x/2;
			int sy = slots[i].getPosition().y+dims.y/2;
			float distance = sqrt(pow(m.x-sx, 2)+pow(m.y-sy, 2) * 1.0);
			if(distance < shortestDistance) {
				// Allow only stacks with 1 card to upper stacks
				int cNum = cards[stacks.back()[0]].getNumber();
				int cSuit = cards[stacks.back()[0]].getSuit();
				sf::Color cCol = cards[stacks.back()[0]].getText().getFillColor();
				if(i >= 6 || (i < 6 && stacks.back().size() == 1)) {
					if(i == 1 && prevStack == 1) { // Card picked from dealt cards
						closestStack = i; // Can return back to dealt cards if not placed anywhere
						shortestDistance = distance;
					}	else { // In other cases like if stack is empty
						if(stacks[i].empty() && (cNum == 1 && i < 6 || cNum == 13 && i >= 6)) {
							closestStack = i; // Then only ace or king is allowed
							shortestDistance = distance;
						} else if (!stacks[i].empty()) { // If stack is not empty then depending on the game rules
							int dNum = cards[stacks[i].back()].getNumber();
							int dSuit = cards[stacks[i].back()].getSuit();
							sf::Color dCol = cards[stacks[i].back()].getText().getFillColor();
							if((cNum == dNum+1 && cSuit == dSuit && i < 6) ||
										(cNum == dNum-1) && !areSameColor(cCol, dCol)) {
								closestStack = i; // Allow ascending same suit cards to top level
								shortestDistance = distance;
							}
					 	}
					}
				}
			}
		}
	}
	return closestStack;
}
