#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "objectpositioner.hpp"
#include "card.hpp"

//Constructor
ObjectPositioner::ObjectPositioner(sf::Color bg, sf::Vector2f dims) {
	bgColor = bg;
	cardDimensions = dims;
}
//Destructor
ObjectPositioner::~ObjectPositioner() {
	std::cout << "Object positioner is destroyed" << std::endl;
}

//Functions
void ObjectPositioner::positionCardSlots(std::string f) {
	std::ifstream slotPositions(f); //Holds card slot positions (x,y)
	int x, y; //Store current positions of the card
	while (slotPositions >> x >> y) { //Read positions for card slots from file
		sf::RectangleShape cardSlot(cardDimensions); //Card slot with shape
		cardSlot.setOutlineColor(sf::Color::Red); //Cardslot outline color TODO change to parameter
		cardSlot.setFillColor(sf::Color::Transparent); //Cardslot has no filled color
		cardSlot.setOutlineThickness(5); //Outline thickness 
		cardSlot.setPosition(x,y); //Set position
		cardSlots.push_back(cardSlot); //Add to the vector that will be drawn in mainloop
	}
}

void ObjectPositioner::createCards(int suits, sf::Vector2f xy, sf::Color cardCol) {
	std::cout << suits << xy.x << xy.y << std::endl;
}

std::vector<sf::RectangleShape> ObjectPositioner::getCardSlotPositions() {
	return cardSlots;
}
