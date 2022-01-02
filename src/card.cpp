// Copyright 2021 Mika-Matti Auerkallio

#include "card.hpp"

// Constructor
Card::Card(sf::Color bg, int n, int s, sf::Vector2f xy, sf::Vector2f dims, sf::Text t,
				sf::Sprite sprite) {
	bgColor = bg;
	number = n;
	suit = s;
	shape = sf::RectangleShape(dims);
	// shape.setPosition(xy);
	shape.setOutlineColor(sf::Color::Black); // Outline of card
	shape.setFillColor(bg);	// Color of card background
	shape.setOutlineThickness(3); // Outline thickness

	text = t; // Set text
  setText(n);	// Set the number of card
	text.setFillColor((s % 2 == 0) ? sf::Color::Red : sf::Color::Black);

	symbol = sprite; // Set the suit symbol for card
	updatePosition(xy);	// Set position for all card elements
}

// Destructor
Card::~Card() { }

// Method declarations
int Card::getNumber() {
	return number;
}

int Card::getSuit() {
	return suit;
}

sf::RectangleShape Card::getDrawable() {
	return shape;
}

sf::Text Card::getText() {
	return text;
}

sf::Sprite Card::getSymbol() {
	return symbol;
}

void Card::setText(int n) {
	switch (n) {
		case 1:
			text.setString("A");
			break;
		case 13:
			text.setString("K");
			break;
		case 12:
			text.setString("Q");
			break;
		case 11:
			text.setString("J");
			break;
		default:
			text.setString(std::to_string(n));
			break;
	}
}

void Card::updatePosition(sf::Vector2f pos) {
	shape.setPosition(pos); // Update card position
	sf::Vector2f dims = shape.getSize(); // Take the size of the card

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
	text.setPosition(pos.x+10+textRect.width/2, pos.y+10+textRect.height/2); // Update numberposition

	sf::FloatRect symbRect = symbol.getLocalBounds();
	symbol.setOrigin(symbRect.width/2, symbRect.height/2);
	symbol.setPosition(pos.x+(dims.x/2), pos.y+(dims.y/2)); // Update symbol coordination
}

void Card::updateOutline(sf::Color c) {
	shape.setOutlineColor(c);
}

bool Card::hasOutline(sf::Color c) {
	sf::Color col = shape.getOutlineColor();
	if(col.r == c.r && col.g == c.g && col.b == c.b) {
		return true;
	}
	return false;
}

bool Card::isFlipped() {
	return flipped;
}

void Card::setFlipped(bool t) {
	flipped = t;
}
