// Copyright 2021 Mika-Matti Auerkallio

#ifndef SRC_OBJECTPOSITIONER_HPP_
#define SRC_OBJECTPOSITIONER_HPP_
#include <vector>
#include <string>

class Card; // Forward declaration of Card class

class ObjectPositioner {
	private:
		sf::Color bgColor;
		sf::Vector2f cardDimensions;
		std::vector<sf::RectangleShape> cardSlots; // Store the slots for cards
	public:
		ObjectPositioner(sf::Color bg, sf::Vector2f dims); // Constructor
		~ObjectPositioner(); // Destructor

		// Method declarations
		void positionCardSlots(std::string file); // Set card slot positions from file
		std::vector<sf::RectangleShape> getCardSlotPositions(); // Get the card slots for rendering
		std::vector<Card> createCards(int suits, sf::Vector2f xy, sf::Color cardCol, sf::Text t,
						const std::vector<sf::Texture>& texs);
		float adjustPositioningSpeed(const float& a, const float& b);
		void getNextCardPos(float &offSet, sf::Vector2f &cardPos, sf::Vector2f &destPos);
		bool mouseIsOverObject(sf::Vector2f object, sf::Vector2i mouse);
};
#endif	// SRC_OBJECTPOSITIONER_HPP_
