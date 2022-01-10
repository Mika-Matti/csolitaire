// Copyright 2021 Mika-Matti Auerkallio

#ifndef SRC_GAMEFUNCTIONS_HPP_
#define SRC_GAMEFUNCTIONS_HPP_

#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <string>
#include "SFML/Graphics.hpp"
#include "card.hpp"

// Function declarations
bool areSameColor(sf::Color a, sf::Color b);
void popFromAndPushTo(std::vector<int> &a, std::vector<int> &b, int &x);
void resetDrawOrder(std::vector<std::vector<int>> &stacks, std::vector<Card> &cards);
std::string setFormattedText(sf::Text &text, std::string str);
std::string getTime(sf::Clock &clock);
std::string updateMouseCoords(sf::Vector2f &mouseCoords, sf::RenderWindow &window);
void centerText(sf::Text &text, float width, float height);
bool moveIsLegal(std::vector<Card> &cards, std::vector<int> &stack, std::pair<int, int> &select);
bool haveWinConditions(std::vector<Card> &cards, std::vector<std::vector<int>> &stacks);
int findClosestStack(std::vector<Card> &cards, std::vector<sf::RectangleShape> &slots,
			std::vector<std::vector<int>> &stacks, int &prevStack, sf::Vector2f &m);

#endif // SRC_GAMEFUNCTIONS_HPP_
