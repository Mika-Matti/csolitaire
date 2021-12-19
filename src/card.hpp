class Card {
	private:
		sf::Color bgColor;
		sf::Color outLine;				 //Will change color when active
		int number; 					//From 1-13
		int suit; 						//Where 1 2 3 4 are spades, clubs, diamonds, hearts
		sf::RectangleShape shape;		//Card shape
	public:
		Card(sf::Color bg, int n, int s, sf::Vector2f xy, sf::Vector2f dims);	//Constructor 
		~Card();	//Destructor
	
		//Method declarations
		sf::RectangleShape getDrawable();
		void updatePosition(sf::Vector2f pos);
};
