//
// Created by andgel on 06/10/2020.
//

#include <iostream>
#include "Resources/version.hpp"
#include "Rendering/Screen.hpp"

int main()
{
	sf::Image logo;
	UntilBeingCrowned::Rendering::Screen screen{
		"Until Being Crowned " UBC_VERSION_STRING, 640, 480
	};
	sf::Event event;

	if (logo.loadFromFile("assets/icon.png"))
		screen.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
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