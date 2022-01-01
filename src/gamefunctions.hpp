// Copyright 2021 Mika-Matti Auerkallio

#ifndef SRC_GAMEFUNCTIONS_HPP_
#define SRC_GAMEFUNCTIONS_HPP_

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "SFML/Graphics.hpp"
#include "card.hpp"
#include "objectpositioner.hpp"

// Function declarations
bool areSameColor(sf::Color a, sf::Color b);
void popFromAndPushTo(std::vector<int> &a, std::vector<int> &b, int &x);
void resetDrawOrder(std::vector<std::vector<int>> &stacks, std::vector<Card> &cards);
std::string updateMouseCoords(sf::Vector2f &mouseCoords, sf::RenderWindow &window);
void highLightText(sf::Text &text, ObjectPositioner &op, sf::Vector2f &mouseCoords);
void highLightCard(std::vector<Card> &cards, std::vector<std::vector<int>> &stacks,
			std::pair<int, int> &select, ObjectPositioner &op, sf::Vector2f &mouseCoords);
bool moveIsLegal(std::vector<Card> &cards, std::vector<int> &stack, std::pair<int, int> &select);

#endif // SRC_GAMEFUNCTIONS_HPP_
