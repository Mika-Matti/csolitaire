// Copyright 2021 Mika-Matti Auerkallio
#include "popup.hpp"

Popup::Popup(sf::RectangleShape s, sf::Text t) { // Constructor
	shape = s;
	sf::Text close = t; // Copy text here too
	close.setString("RETURN");

	// Center the title text and place it to the top of shape
	sf::FloatRect textRect = t.getLocalBounds();
	t.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
	t.setPosition(s.getPosition().x+s.getSize().x/2, s.getPosition().y+20+textRect.height/2);

	// Center the close text and place it above the bottom of shape
	textRect = close.getLocalBounds();
	close.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
	close.setPosition(s.getPosition().x+s.getSize().x/2,
				s.getPosition().y+s.getSize().y-35+textRect.height/2);

	// Store the texts into the vector of texts
	texts.push_back(t);
	texts.push_back(close); // This should always be the last in the vector
}

Popup::~Popup() { } // Deconstructor

// Method declarations
sf::RectangleShape Popup::getShape() {
	return shape;
}

std::vector<sf::Text>& Popup::getTexts() {
	return texts;
}
