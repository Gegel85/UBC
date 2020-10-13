//
// Created by andgel on 06/10/2020.
//

#include <iostream>
#include "Resources/version.hpp"
#include "Rendering/Screen.hpp"
#include "Resources/Logger.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"
#include "Resources/Game.hpp"
#include "Loader.hpp"

int main()
{
#ifndef _DEBUG
	try {
#endif
	sf::Event event;
	UntilBeingCrowned::Game game;

	UntilBeingCrowned::Loader::loadAssets(game);
	while (game.resources.screen.isOpen()) {
		while (game.resources.screen.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				game.resources.screen.close();
			}
		}
		game.resources.screen.display();
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