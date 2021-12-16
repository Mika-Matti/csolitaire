class ObjectPositioner {
	private:
		sf::Color bgColor;	
		std::vector<sf::RectangleShape> cardSlots; //Store the slots for cards
	public:
		ObjectPositioner(sf::Color bg);	//Constructor declaration
		~ObjectPositioner();			//Destructor declaration

		//Method declarations
		void positionCardSlots(std::string file);
		std::vector<sf::RectangleShape> getCardSlotPositions();
};
