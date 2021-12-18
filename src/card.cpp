#include <SFML/Graphics.hpp>
#include <iostream>
#include "card.hpp"

//Constructor
Card::Card(sf::Color bg, int n, int s, sf::Vector2f xy) {
	bgColor = bg;
	number = n;
	suit = s;
	pos = xy;
}

//Destructor
Card::~Card() {
	std::cout << "Card " << suit << " " << number << " destroyed" << std::endl;
}
//Method declarations
sf::Vector2f Card::getCardPos() {
	return pos;
}
