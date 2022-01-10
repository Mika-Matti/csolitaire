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

std::string getTime(sf::Clock &clock) {
	std::string timeString = "00:00:00";
	int time = static_cast<int>(clock.getElapsedTime().asSeconds());
	std::string hours = std::to_string(time/3600);
	std::string minutes = std::to_string((time/60)%60);
	std::string seconds = std::to_string(time%60);
	if(hours.size() < 2) // Maintain fixed format
		hours = "0" + hours;
	if(minutes.size() < 2)
		minutes = "0" + minutes;
	if(seconds.size() < 2)
		seconds = "0" + seconds;

	timeString = hours + ":" + minutes + ":" + seconds;

	return timeString;
}

std::string setFormattedText(sf::Text &text, std::string str) {
	std::string t = text.getString();
	str.insert(str.begin(), t.length()-str.length(), '0');
	return str;
}

std::string updateMouseCoords(sf::Vector2f &mouseCoords, sf::RenderWindow &window) {
	std::string coords = "";
	mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	std::string x = std::to_string(mouseCoords.x);
	std::string y = std::to_string(mouseCoords.y);
	coords = x.substr(0, x.find(".")) + ", "	+ y.substr(0, y.find("."));
	return coords;
}

void centerText(sf::Text &text, float width, float height) {
	// Center the text and place it to the middle of given width and height
	sf::FloatRect textRect = text.getLocalBounds();
	sf::Vector2f pos = text.getPosition();
	text.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
	text.setPosition(pos.x+width/2.0, pos.y+height/2);
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
					if(i == prevStack) { // If closest is the previous stack
						closestStack = i; // Can return back to dealt cards if not placed anywhere
						shortestDistance = distance;
					}	else { // In other cases like if stack is empty
						if(stacks[i].empty() && (cNum == 1 && i < 6 || cNum == 13 && i >= 6)) {
							closestStack = i; // Then only ace or king is allowed
							shortestDistance = distance;
						} else if (!stacks[i].empty()) { // If stack is not empty then depending on game rules
							int dNum = cards[stacks[i].back()].getNumber();
							int dSuit = cards[stacks[i].back()].getSuit();
							sf::Color dCol = cards[stacks[i].back()].getText().getFillColor();
							if((cNum == dNum+1 && cSuit == dSuit && i < 6) ||
										(cNum == dNum-1) && !areSameColor(cCol, dCol) && i >= 6) {
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
