#ifndef CARD_H
#define CARD_H
class Card {
	private:
		sf::Color bgColor;
		sf::Color outLine;				//Will change color when active
		int number; 					//From 1-13
		int suit; 						//Where 1 2 3 4 are spades, diamonds, clubs, hearts
		sf::RectangleShape shape;		//Card shape
		sf::Text text;
	public:
		Card(sf::Color bg, int n, int s, sf::Vector2f xy, sf::Vector2f dims, sf::Text t); 
		~Card();	//Destructor
	
		//Method declarations
		int getNumber();
		sf::RectangleShape getDrawable();
		sf::Text getText();
		void updatePosition(sf::Vector2f pos);
};
#endif
