//
// Created by andgel on 06/10/2020.
//

#include <iostream>
#include "Rendering/Screen.hpp"

int main()
{
	UntilBeingCrowned::Rendering::Screen screen{
		"", 640, 480
	};
	sf::Event event;

	while (screen.isOpen()) {
		while (screen.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen.close();
			}
		}
		screen.display();
	}
	return EXIT_SUCCESS;
}