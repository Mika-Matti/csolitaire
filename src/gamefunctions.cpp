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
