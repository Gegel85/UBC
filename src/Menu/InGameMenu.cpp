//
// Created by andgel on 15/10/2020.
//

#include "InGameMenu.hpp"

namespace UntilBeingCrowned
{
	InGameMenu::InGameMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, DialogMgr &dialogs) :
		_res(res),
		_gui(gui),
		_mgr(mgr),
		_dialogs(dialogs)
	{
	}

	void InGameMenu::switched(bool isActive)
	{
		if (!isActive) {
			this->_gui.removeAllWidgets();
			return;
		}

		auto pic = tgui::Picture::create(this->_res.textures["igproto"]);

		pic->setSize("&.w", "&.h");
		pic->setPosition(0, 0);
		this->_gui.add(pic, "base");
		this->_dialogs.showDialog("dialogs.json", 0, this->_gui);
	}

	void InGameMenu::render()
	{

	}

	void InGameMenu::handleEvent(const Input::Event &)
	{

	}
}
