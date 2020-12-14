//
// Created by andgel on 18/11/2020.
//

#include "VictoryMenu.hpp"
#include "Exceptions.hpp"

namespace UntilBeingCrowned
{
	VictoryMenu::VictoryMenu(MenuMgr &mgr, Resources &res, tgui::Gui &gui, GameState &state) :
		_mgr(mgr),
		_gui(gui),
		_state(state),
		_res(res)
	{
	}

	void VictoryMenu::switched(bool isActive)
	{
		if (!isActive)
			return;

		this->_res.playMusic("win");
		auto it = std::find_if(this->_state.flags.begin(), this->_state.flags.end(), [](const std::string &str){
			return str.substr(0, strlen("victory_")) == "victory_";
		});
		auto it2 = this->_res.endMessages.find(*it);

		if (it2 == this->_res.endMessages.end())
			throw InvalidEndException("No end exists with id " + *it);

		this->_gui.loadWidgetsFromFile("gui/victory_menu.gui");

		auto box = this->_gui.get<tgui::TextBox>("TextBox");

		box->setText(it2->second);
		box->setVerticalScrollbarValue(0);
		this->_gui.get<tgui::Button>("menu")->connect(
			"Clicked",
			[this]{
				this->_res.playSound("click_button");
				this->_mgr.changeMenu("main");
			}
		);
	}

	void VictoryMenu::render()
	{
	}

	void VictoryMenu::handleEvent(const Input::Event &)
	{

	}
}
