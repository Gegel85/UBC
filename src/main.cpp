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
#include "Menu/LoadingMenu.hpp"
#include "Menu/GenderMenu.hpp"
#include "Menu/DialogMenu.hpp"
#include "Menu/VictoryMenu.hpp"
#include "Menu/GameoverMenu.hpp"

namespace UntilBeingCrowned
{
	void init(Game &game)
	{
		UntilBeingCrowned::Loader::loadAssets(game);
		sf::View view{
			{680, 384},
			{1360, 768}
		};

		game.state.gui.setTarget(game.resources.screen);
		game.state.gui.setView(view);
		game.state.menuMgr.addMenu<VictoryMenu>("victory", game.resources, game.state.gui, game.state.game);
		game.state.menuMgr.addMenu<GameoverMenu>("game over", game.resources, game.state.gui, game.state.game);
		game.state.menuMgr.addMenu<InGameMenu>("in_game", game.state.gui, game.resources, game.state.questMgr, game.state.game);
		game.state.menuMgr.addMenu<DialogMenu>("dialog", game.resources, game.state.gui, game.state.dialogMgr, game.state.game);
		game.state.menuMgr.addMenu<MainMenu>("main", game.state.gui, game.resources, game);
		game.state.menuMgr.addMenu<OptionMenu>("option", game.state.gui, game.resources, game);
		game.state.menuMgr.addMenu<LoadingMenu>("load", game.state.gui, game.resources);
		game.state.menuMgr.addMenu<GenderMenu>("gender", game.state.gui, game.resources, game.state.game, game.state.questMgr);
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
		game.resources.screen.clear();
		game.state.menuMgr.renderMenu();
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