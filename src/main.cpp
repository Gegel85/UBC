//
// Created by andgel on 06/10/2020.
//

#include "Resources/Game.hpp"
#include "Rendering/Screen.hpp"
#include "Resources/Logger.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"
#include "Loader.hpp"
#include "Menu/InGameMenu.hpp"
#include "Menu/MainMenu.hpp"
#include "Menu/OptionMenu.hpp"
#include "Menu/LoadMenu.hpp"

namespace UntilBeingCrowned
{
	void init(Game &game)
	{
		UntilBeingCrowned::Loader::loadAssets(game);

		game.state.gui.setTarget(game.resources.screen);
		//game.state.menuMgr.addMenu<InGameMenu>("in_game", game.state.gui, game.resources, game.state.questMgr);
        game.state.menuMgr.addMenu<MainMenu>("main", game.state.gui, game.resources, game.state.questMgr);
        game.state.menuMgr.addMenu<OptionMenu>("option", game.state.gui, game.resources, game.state.questMgr);
        game.state.menuMgr.addMenu<LoadMenu>("load", game.state.gui, game.resources, game.state.questMgr);
        game.state.menuMgr.changeMenu("main");
	}
}

int main()
{
#ifndef _DEBUG
	try {
#endif
	sf::Event event;
	UntilBeingCrowned::Game game;

	UntilBeingCrowned::init(game);
	while (game.resources.screen.isOpen()) {
		while (game.resources.screen.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				game.resources.screen.close();
			game.state.gui.handleEvent(event);
		}
		game.state.menuMgr.renderMenu();
		game.resources.screen.clear();
		game.state.gui.draw();
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