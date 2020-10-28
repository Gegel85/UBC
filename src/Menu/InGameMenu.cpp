//
// Created by andgel on 15/10/2020.
//

#include "InGameMenu.hpp"

namespace UntilBeingCrowned
{
	InGameMenu::InGameMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs, GameState &state) :
		_res(res),
		_gui(gui),
		_mgr(mgr),
		_dialogs(dialogs),
		_state(state)
	{
	}

	void InGameMenu::switched(bool isActive)
	{
		if (!isActive) {
			this->_gui.removeAllWidgets();
			return;
		}
		this->_gui.loadWidgetsFromFile("gui/igmenu.gui");
		this->_dialogs.showDialog("quests.json", 0, this->_state, this->_gui);
	}

	void InGameMenu::render()
	{
		this->_res.screen.draw(
			this->_res.textures["igproto"],
			{0, 0},
			this->_res.screen.getSize()
		);
	}

	void InGameMenu::handleEvent(const Input::Event &)
	{

	}
}
