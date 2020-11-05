//
// Created by Gegel85 on 25/09/2019.
//

#include <iostream>
#include "MenuMgr.hpp"
#include "Exceptions.hpp"

namespace UntilBeingCrowned
{
	void MenuMgr::handleEvent(const Input::Event &event)
	{
		if (!this->_currentMenu.empty())
			this->_menus.at(this->_currentMenu)->handleEvent(event);
	}

	void MenuMgr::renderMenu()
	{
		if (!this->_currentMenu.empty())
			this->_menus.at(this->_currentMenu)->render();
	}

	void MenuMgr::changeMenu(const std::string &newMenu)
	{
		if (this->_menus.find(newMenu) == this->_menus.end())
			throw InvalidMenuException("No menu is named " + newMenu);

		if (!this->_currentMenu.empty())
			this->_menus.at(this->_currentMenu)->switched(false);
		this->_menus[newMenu]->switched(true);
		this->_currentMenu = newMenu;
	}
}