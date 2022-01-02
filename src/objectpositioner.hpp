// Copyright 2021 Mika-Matti Auerkallio

#ifndef SRC_OBJECTPOSITIONER_HPP_
#define SRC_OBJECTPOSITIONER_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "card.hpp"

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
		sf::RectangleShape createRectangle(sf::Vector2f dims, sf::Vector2f pos,
													sf::Color outLine, sf::Color fill, int edgeSize);
		std::vector<Card> createCards(int suits, sf::Vector2f xy, sf::Color cardCol, sf::Text t,
						const std::vector<sf::Texture>& texs);
		float adjustPositioningSpeed(const float& a, const float& b);
		void getNextCardPos(sf::Vector2f &cardPos, sf::Vector2f &destPos);
		bool moveCard(Card &card, sf::Vector2f destPos, sf::Vector2f offSet, int stack);
		bool mouseIsOverObject(sf::Vector2f object, sf::Vector2f size, sf::Vector2f mouse);
		void compressStack(std::vector<Card> &cards, std::vector<int> &stack,
						float &max, float &stackOffsetY);
};
#endif	// SRC_OBJECTPOSITIONER_HPP_
