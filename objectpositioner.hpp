class ObjectPositioner {
	private:
		sf::Color bgColor;	
		std::vector<sf::RectangleShape> cardSlots; //Store the slots for cards
		//TODO Store card objects into 13 stacks. Use the slot coord for card coords.
	public:
		ObjectPositioner(sf::Color bg);	//Constructor declaration
		~ObjectPositioner();			//Destructor declaration

		//Method declarations
		void positionCardSlots(std::string file); //Set card slot positions from file
		std::vector<sf::RectangleShape> getCardSlotPositions(); //Get the card slots for rendering
		//TODO Create the cards and store them into the 13 stacks of slots.
		//TODO Get card stacks in vector form for rendering to window
};
