class Card; //Forward declaration of Card class

class ObjectPositioner {
	private:
		sf::Color bgColor;	
		sf::Vector2f cardDimensions;
		std::vector<sf::RectangleShape> cardSlots; //Store the slots for cards
		std::vector<Card> cards; //Store cards. Use slot coords to base card coords.
	public:
		ObjectPositioner(sf::Color bg, sf::Vector2f dims);	//Constructor declaration
		~ObjectPositioner();			//Destructor declaration

		//Method declarations
		void positionCardSlots(std::string file); //Set card slot positions from file
		std::vector<sf::RectangleShape> getCardSlotPositions(); //Get the card slots for rendering
		std::vector<sf::RectangleShape> makeCardDrawables(); //Make the cards for rendering
		void createCards(int suits, sf::Vector2f xy, sf::Color cardCol); //cards to vector
		std::vector<Card> getCards();
		//TODO shuffle card vector
};