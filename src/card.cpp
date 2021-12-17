#include <SFML/Graphics.hpp>
#include <iostream>
#include "card.hpp"

//Constructor
Card::Card(sf::Color bg, int n, int s, int x, int y) {
	bgColor = bg;
	number = n;
	suit = s;
	x = x;
	y = y;
}
//Destructor
Card::~Card() {
	std::cout << "Card destroyed" << std::endl;
}
//Method declarations
