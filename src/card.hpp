// Copyright 2021 Mika-Matti Auerkallio

#ifndef SRC_CARD_HPP_
#define SRC_CARD_HPP_
class Card {
	private:
		sf::Color bgColor;
		sf::Color outLine; // Will change color when active
		int number; // From 1-13
		int suit; // Where 1 2 3 4 are spades, diamonds, clubs, hearts
		sf::RectangleShape shape;	// Drawable card shape
		sf::Text text; // Drawable card number
		sf::Sprite symbol; // Drawable card suit symbol
	public:
		Card(sf::Color bg, int n, int s, sf::Vector2f xy, sf::Vector2f dims,
					    sf::Text t, sf::Sprite sprite);
		~Card(); // Destructor

		// Method declarations
		int getNumber();
		sf::RectangleShape getDrawable();
		sf::Text getText();
		sf::Sprite getSymbol();
		void updatePosition(sf::Vector2f pos);
};
#endif // SRC_CARD_HPP_
