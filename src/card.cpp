#include <SFML/Graphics.hpp>
#include <iostream>
#include "card.hpp"

//Constructor
Card::Card(sf::Color bg, int n, int s, sf::Vector2f xy, sf::Vector2f dims) {
	bgColor = bg;
	number = n;
	suit = s;
	shape = sf::RectangleShape(dims); //TODO replace with parameter
	shape.setPosition(xy);
	shape.setOutlineColor(sf::Color::Black); //TODO get from parameter
	shape.setFillColor(bg);
	shape.setOutlineThickness(1); //Outline thickness
}

//Destructor
Card::~Card() {
	//std::cout << "Card " << suit << " " << number << " destroyed" << std::endl;
}
//Method declarations
sf::RectangleShape Card::getDrawable() {
	return shape;
}
