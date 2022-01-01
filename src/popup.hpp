// Copyright 2021 Mika-Matti Auerkallio

#ifndef SRC_POPUP_HPP_
#define SRC_POPUP_HPP_

#include <iostream>
#include <vector>
#include "popup.hpp"
#include "SFML/Graphics.hpp"

class Popup {
	private:
		sf::RectangleShape shape; // Base shape of window
		std::vector<sf::Text> texts; // Vector to store rows of text in

	public:
		Popup(sf::RectangleShape s, sf::Text t); // Constructor
		~Popup(); // Destructor

	// Method declarations
	sf::RectangleShape getShape();
	std::vector<sf::Text>& getTexts();
};
#endif // SRC_POPUP_HPP_
