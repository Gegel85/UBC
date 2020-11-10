//
// Created by timcav on 10/11/2020.
//

#include "GenderMenu.hpp"


namespace UntilBeingCrowned {
	GenderMenu::GenderMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs) :
			_res(res),
			_gui(gui),
			_mgr(mgr),
			_dialogs(dialogs),
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
		this->_gui.get<tgui::Button>("femaleButton")->connect(tgui::Signals::Button::Pressed, GenderMenu::girlButtonHandler, std::ref(*this));
		this->_gui.get<tgui::Button>("maleButton")->connect(tgui::Signals::Button::Pressed, GenderMenu::boyButtonHandler, std::ref(*this));

	}

	void GenderMenu::render() {

	}

	void GenderMenu::handleEvent(const Input::Event &) {

	}

	void GenderMenu::launchAsGirl() {
		// TODO : set as girl
		this->_mgr.changeMenu(_nexLevel);
	}

	void GenderMenu::launchAsBoy() {
		// TODO : set as a boy
		this->_mgr.changeMenu(_nexLevel);
	}

	void GenderMenu::girlButtonHandler(GenderMenu &m) {
		m.launchAsGirl();
	}

	void GenderMenu::boyButtonHandler(GenderMenu &m) {
		m.launchAsBoy();
	}
}