class Card {
	private:
		sf::Color bgColor;
		sf::Color outLine;		 //Will change color when active
		int number; 			//From 1-13
		int suit; 				//Where 0 1 2 3 are spades, clubs, diamonds, hearts
		sf::Vector2f pos;		//Card position
	public:
		Card(sf::Color bg, int n, int s, sf::Vector2f xy);		//Constructor declaration
		~Card();												//Destructor declaration
	
		//Method declarations
		sf::Vector2f getCardPos();
};
