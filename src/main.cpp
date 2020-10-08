//
// Created by andgel on 06/10/2020.
//

#include <iostream>
#include "Resources/version.hpp"
#include "Rendering/Screen.hpp"
#include "Resources/Logger.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"

int main()
{
#ifndef _DEBUG
	try {
#endif
	sf::Image logo;
	UntilBeingCrowned::Rendering::Screen screen{
		"Until Being Crowned " UBC_VERSION_STRING, 640, 480
	};
	sf::Event event;

	if (logo.loadFromFile("assets/icon.png"))
		screen.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
	else
		UntilBeingCrowned::logger.error("Cannot open file assets/icon.png");

	while (screen.isOpen()) {
		while (screen.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen.close();
			}
		}
		screen.display();
	}
#ifndef _DEBUG
	} catch (std::exception &e) {
		UntilBeingCrowned::logger.fatal(getLastExceptionName() + ": " + e.what());
		UntilBeingCrowned::Utils::dispMsg(
			"Fatal Error",
			"An unrecoverable error occurred\n\n" +
			getLastExceptionName() + ":\n" + e.what() + "\n\n"
			"Click OK to close the application",
			MB_ICONERROR
		);
	}
#endif
	return EXIT_SUCCESS;
}