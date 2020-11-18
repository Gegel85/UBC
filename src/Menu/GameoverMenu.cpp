//
// Created by andgel on 18/11/2020.
//

#include "GameoverMenu.hpp"

namespace UntilBeingCrowned
{
	GameoverMenu::GameoverMenu(MenuMgr &mgr, tgui::Gui &gui, GameState &state) :
		_mgr(mgr),
		_gui(gui),
		_state(state)
	{
	}

	void GameoverMenu::switched(bool isActive)
	{
		if (!isActive)
			return;

		auto it = std::find_if(this->_state.flags.begin(), this->_state.flags.end(), [](const std::string &str){
			return str.substr(0, strlen("killed_")) == "killed_";
		});

		this->_gui.loadWidgetsFromFile("gui/gameover_menu.gui");
		this->_gui.get<tgui::Label>("EndId")->setText(*it);
		this->_gui.get<tgui::Button>("menu")->connect("Clicked", &MenuMgr::changeMenu, &this->_mgr, "main");
	}

	void GameoverMenu::render()
	{
	}

	void GameoverMenu::handleEvent(const Input::Event &)
	{

	}
}
