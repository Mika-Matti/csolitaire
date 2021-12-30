// Copyright 2021 Mika-Matti Auerkallio

#include <iostream>
#include <vector>
#include <utility>
#include "SFML/Graphics.hpp"
#include "card.hpp"
#include "gamefunctions.hpp"

// Function definitions
bool areSameColor(sf::Color &a, sf::Color &b) {
	if(a.r == b.r && a.g == b.g && a.b == b.b) {
		return true;
	}
	return false;
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
