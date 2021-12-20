#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "card.hpp"
#include "objectpositioner.hpp"

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

//std::vector<sf::RectangleShape> ObjectPositioner::makeCardDrawables() {
//	std::vector<sf::RectangleShape> drawableCards;
//	float xOffset = 0.0f, yOffset = 0.0f;

//	for(int i=0; i<cards.size(); i++) {
//		sf::Vector2f cardPos = cards[i].getCardPos();
//
//		sf::RectangleShape drawable(cardDimensions); //Card shape
//		drawable.setOutlineColor(sf::Color::Black); //Cardslot outline color TODO change to parameter
//		drawable.setFillColor(sf::Color::White); //TODO get this from card class
//		drawable.setOutlineThickness(1); //Outline thickness
//		if(i > 0 && cardPos.x != cards[i-1].getCardPos().x && 
//						cardPos.y != cards[i-1].getCardPos().y) { //If stack changes
//			xOffset = 0.0f;	//Then reset offsets of the stack being filled
//			yOffset = 0.0f;
//		}
		//For row to stack this will make the cosmetic effect of stacking cards
//		if(cardPos.y == 20) { //If card is in slot that is upper level
//			xOffset = xOffset+0.1f;
//			yOffset = yOffset-0.1f;
//		} else {
			//Make the cosmetic effect of cards stacking 
//		}
//		drawable.setPosition(cardPos.x + xOffset, cardPos.y + yOffset); //Set position
//		drawableCards.push_back(drawable); //Add to the vector that will be drawn in mainloop
//	}
//	return drawableCards;
//}

std::vector<Card> ObjectPositioner::createCards(int suits, sf::Vector2f xy, sf::Color cardCol, sf::Text t, const std::vector<sf::Texture>& texs) {
	std::vector<Card> cards;			//Initiate vector
	int size = suits*13;				//Calculate size for vector
	cards.reserve(size);				//Allocate size in vector
	for(int i=1; i<=suits; i++)			//For every suit
		for(int a=1; a<=13; a++)		//For every card in a suit
			cards.push_back(Card(cardCol, i, a, xy, cardDimensions, t));//Add the card to the vector
	return cards;
}

std::vector<sf::RectangleShape> ObjectPositioner::getCardSlotPositions() {
	return cardSlots;
}
