class Card {
	private:
		sf::Color bgColor;
		sf::Color outLine; //Will change color when active
		int number; 	//From 1-13
		int suit; 		//Where 0 1 2 3 are spades, clubs, diamonds, hearts
		int x,y;		//Card position
	public:
		Card(sf::Color bg, int n, int s, int x, int y);		//Constructor declaration
		~Card();											//Destructor declaration
	
		//Method declarations
};
