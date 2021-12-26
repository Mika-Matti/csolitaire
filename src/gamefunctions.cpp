// Copyright 2021 Mika-Matti Auerkallio

#include <vector>
#include <utility>
#include "SFML/Graphics.hpp"
#include "card.hpp"
#include "gamefunctions.hpp"

// Function definitions

bool moveIsLegal(std::vector<Card> &cards, std::pair<int, int> &highLighted) {
	if(cards[highLighted.second].hasOutline(sf::Color::Yellow) &&
		(highLighted.first == 0 && cards[highLighted.second].isFlipped() ||
		highLighted.first > 0 && !cards[highLighted.second].isFlipped())) {
		return true;
	}
	return false;
}
