#include <SFML/Graphics.hpp>
#include <iostream>
#include "card.hpp"

//Constructor
Card::Card(sf::Color bg, int n, int s, sf::Vector2f xy, sf::Vector2f dims, sf::Text t) {
	bgColor = bg;
	number = n;
	suit = s;
	shape = sf::RectangleShape(dims);
	shape.setPosition(xy);
	shape.setOutlineColor(sf::Color::Black); //Outline of card
	shape.setFillColor(bg);	//Color of card background
	shape.setOutlineThickness(1); //Outline thickness
	
	text = t;
	text.setString(std::to_string(s)); //Set number of card
	text.setCharacterSize(24); //Text size in pixels
	text.setFillColor((s % 2 == 0) ? sf::Color::Red : sf::Color::Black);
	text.setPosition(xy);		//Position of number
}

//Destructor
Card::~Card() {
	//std::cout << "Card " << suit << " " << number << " destroyed" << std::endl;
}
//Method declarations
int Card::getNumber() {
	return number;
}

sf::RectangleShape Card::getDrawable() {
	return shape;
}

sf::Text Card::getText() {
	return text;
}

void Card::updatePosition(sf::Vector2f pos) {
	shape.setPosition(pos);
	sf::Vector2f dims = shape.getSize(); //Take the size of the card
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	text.setPosition(pos.x+(dims.x/2.0f), pos.y+(dims.y/2.0f)); //Center the number to card
}
