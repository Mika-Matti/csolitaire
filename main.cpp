#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "objectpositioner.hpp"

int main() {
	//Initiate objects
	sf::RenderWindow window(sf::VideoMode(960, 540), "CSolitaire"); //Game window
	sf::Color bgColor = sf::Color::Black;
	ObjectPositioner objectPositioner(bgColor);

	//Read positions for card slots from file
	objectPositioner.positionCardSlots("slotpositions.cfg"); //Set card slot positions (x,y)
	std::vector<sf::RectangleShape> cardSlots = objectPositioner.getCardSlotPositions();

	//Start mainloop
	while (window.isOpen()) {
		//Closing mechanism to exit mainloop	
		sf::Event event;
		while (window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}
		//Redraw window
		window.clear(bgColor); //Clear the window
		//Draw the objects on the window		
		for(int i=0; i < cardSlots.size(); i++) {		
			window.draw(cardSlots[i]); 
		}
			//End drawing
		window.display(); //Update the window
	}

	return 0;
}
