// Copyright 2021 Mika-Matti Auerkallio

#include <iostream>
#include <SFML/Graphics.hpp>
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

	text = t;
	// Set the number of card //TODO make this a function
	switch (n) {
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

	text.setFillColor((s % 2 == 0) ? sf::Color::Red : sf::Color::Black);
	// text.setPosition(xy);	// Position of number

	symbol = sprite; // Set the suit symbol for card
	// symbol.setPosition(xy); // Set symbol position
	updatePosition(xy);	// Set position for all card elements
}

// Destructor
Card::~Card() {
	// std::cout << "Card " << suit << " " << number << " destroyed" << std::endl;
}
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

void Card::updatePosition(sf::Vector2f pos) {
	shape.setPosition(pos); // Update card position
	sf::Vector2f dims = shape.getSize(); // Take the size of the card

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	text.setPosition(pos.x+(dims.x/10.0f), pos.y+(dims.y/10.0f)); // Update number position

	sf::FloatRect symbRect = symbol.getLocalBounds();
	symbol.setOrigin(symbRect.width/2.0f, symbRect.height/2.0f);
	symbol.setPosition(pos.x+(dims.x/2.0f), pos.y+(dims.y/2.0f)); // Update symbol coordination
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
