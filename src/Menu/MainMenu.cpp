//
// Created by timcav on 27/10/2020.
//

#include "MainMenu.hpp"

namespace UntilBeingCrowned {
	MainMenu::MainMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res) :
		_res(res),
		_gui(gui),
		_mgr(mgr)
	{
	}

	void MainMenu::switched(bool isActive)
	{
		if (!isActive) {
			this->_gui.removeAllWidgets();
			return;
		}

		this->_gui.loadWidgetsFromFile("gui/mainMenu.gui");

		this->_gui.get<tgui::Button>("newGame")->connect(
			tgui::Signals::Button::Pressed,
			&MenuMgr::changeMenu,
			&this->_mgr,
			"gender"
		);

		this->_gui.get<tgui::Button>("loadGame")->connect(
			tgui::Signals::Button::Pressed,
			&MenuMgr::changeMenu,
			&this->_mgr,
			"load"
		);

		this->_gui.get<tgui::Button>("options")->connect(
			tgui::Signals::Button::Pressed,
			&MenuMgr::changeMenu,
			&this->_mgr,
			"option"
		);

		this->_gui.get<tgui::Button>("exit")->connect(
			tgui::Signals::Button::Pressed,
			&Rendering::Screen::close,
			&this->_res.screen
		);

	}

	void MainMenu::render()
	{

	}

	void MainMenu::handleEvent(const Input::Event &)
	{

	}
}

