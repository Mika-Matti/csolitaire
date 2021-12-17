class ObjectPositioner {
	private:
		sf::Color bgColor;	
		sf::Vector2f cardDimensions;
		std::vector<sf::RectangleShape> cardSlots; //Store the slots for cards
		//TODO Store card objects into a vector. Use the slot coord for card coords.
	public:
		ObjectPositioner(sf::Color bg, sf::Vector2f dims);	//Constructor declaration
		~ObjectPositioner();			//Destructor declaration

		//Method declarations
		void positionCardSlots(std::string file); //Set card slot positions from file
		std::vector<sf::RectangleShape> getCardSlotPositions(); //Get the card slots for rendering
		void createCards(int suits, sf::Vector2f xy, sf::Color cardCol); //cards to vector
		//TODO Get card vector
		//TODO shuffle card vector
};
