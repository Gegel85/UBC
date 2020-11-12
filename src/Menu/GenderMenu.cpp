//
// Created by timcav on 10/11/2020.
//

#include "GenderMenu.hpp"


namespace UntilBeingCrowned
{
	GenderMenu::GenderMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, GameState &state) :
		_res(res),
		_gui(gui),
		_mgr(mgr),
		_state(state),
		_nexLevel("in_game")
	{
	}

	void GenderMenu::switched(bool isActive) {
		if (!isActive) {
			this->_gui.removeAllWidgets();
			return;
		}

		this->_gui.loadWidgetsFromFile("gui/genderMenu.gui");
		//TODO :  set real picture for the buttons
		this->_gui.get<tgui::Button>("femaleButton")->connect(tgui::Signals::Button::Pressed, &GenderMenu::_runGame, this, "player_f");
		this->_gui.get<tgui::Button>("maleButton")->connect(tgui::Signals::Button::Pressed, &GenderMenu::_runGame, this, "player_m");

	}

	void GenderMenu::render() {

	}

	void GenderMenu::handleEvent(const Input::Event &) {

	}
	void GenderMenu::_runGame(const std::string &flag)
	{
		this->_state.flags.push_back(flag);
		this->_mgr.changeMenu(_nexLevel);
	}
}