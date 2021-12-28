// Copyright 2021 Mika-Matti Auerkallio

#ifndef SRC_GAMEFUNCTIONS_HPP_
#define SRC_GAMEFUNCTIONS_HPP_
#include <vector>
#include <utility>

bool areSameColor(sf::Color &a, sf::Color &b);
bool moveIsLegal(std::vector<Card> &cards, std::vector<int> &stack, std::pair<int, int> &select);

#endif // SRC_GAMEFUNCTIONS_HPP_
