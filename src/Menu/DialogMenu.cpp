//
// Created by andgel on 17/11/2020.
//

#include "DialogMenu.hpp"

namespace UntilBeingCrowned
{
	const std::vector<std::string> in_game_musics{
		"in_game_0",
		"in_game_1",
		"in_game_2",
	};

	DialogMenu::DialogMenu(MenuMgr &mgr, Resources &res, tgui::Gui &gui, DialogMgr &dialogs, GameState &state) :
		_mgr(mgr),
		_gui(gui),
		_dialogMgr(dialogs),
		_state(state),
		_res(res)
	{
	}

	DialogMenu::~DialogMenu()
	{
	}

	void DialogMenu::switched(bool isActive)
	{
		if (isActive) {
			this->_gui.loadWidgetsFromFile("gui/dialogMenu.gui");
			this->_dialogMgr.startDialog("week" + std::to_string(this->_state.week));
			for (auto &mus : in_game_musics)
				if (this->_res.musics[mus].first.getStatus() == sf::Music::Playing)
					return;
			this->_res.playMusic(in_game_musics[this->_res.random() % in_game_musics.size()]);
		} else
			this->_gui.removeAllWidgets();
	}

	void DialogMenu::render()
	{
		this->_dialogMgr.update();
		if (this->_dialogMgr.hasSkippedWeek())
			this->switched(true);
		if (this->_dialogMgr.isDone())
			this->_mgr.changeMenu("in_game");
	}

	void DialogMenu::handleEvent(const Input::Event &)
	{

	}
}