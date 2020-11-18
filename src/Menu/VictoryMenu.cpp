//
// Created by andgel on 18/11/2020.
//

#include "VictoryMenu.hpp"

namespace UntilBeingCrowned
{
	VictoryMenu::VictoryMenu(MenuMgr &mgr, tgui::Gui &gui, GameState &state) :
		_mgr(mgr),
		_gui(gui),
		_state(state)
	{
	}

	void VictoryMenu::switched(bool isActive)
	{
		if (!isActive)
			return;

		auto it = std::find_if(this->_state.flags.begin(), this->_state.flags.end(), [](const std::string &str){
			return str.substr(0, strlen("victory_")) == "victory_";
		});

		this->_gui.loadWidgetsFromFile("gui/victory_menu.gui");
		this->_gui.get<tgui::Label>("EndId")->setText(*it);
		this->_gui.get<tgui::Button>("menu")->connect("Clicked", &MenuMgr::changeMenu, &this->_mgr, "main");
	}

	void VictoryMenu::render()
	{
	}

	void VictoryMenu::handleEvent(const Input::Event &)
	{

	}
}
