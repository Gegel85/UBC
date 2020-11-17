//
// Created by andgel on 17/11/2020.
//

#include "DialogMenu.hpp"

namespace UntilBeingCrowned
{

	DialogMenu::DialogMenu(MenuMgr &mgr, tgui::Gui &gui, DialogMgr &dialogs, GameState &state) :
		_mgr(mgr),
		_gui(gui),
		_dialogMgr(dialogs),
		_state(state)
	{
	}

	DialogMenu::~DialogMenu()
	{
	}

	void DialogMenu::switched(bool isActive)
	{
		if (isActive) {
			if (!this->_dialogMgr.hasDialog("week" + std::to_string(this->_state.week)))
				this->_mgr.changeMenu("in_game");
			this->_gui.loadWidgetsFromFile("gui/dialogMenu.gui");
			this->_dialogMgr.startDialog("week" + std::to_string(this->_state.week));
		} else
			this->_gui.removeAllWidgets();
	}

	void DialogMenu::render()
	{
		this->_dialogMgr.update();
	}

	void DialogMenu::handleEvent(const Input::Event &)
	{

	}
}