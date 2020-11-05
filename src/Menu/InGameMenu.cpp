//
// Created by andgel on 15/10/2020.
//

#include "InGameMenu.hpp"
#include "../Resources/State.hpp"

namespace UntilBeingCrowned
{
	InGameMenu::InGameMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs, GameState &state,
						   UntilBeingCrowned::State state1) :
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
		this->_goldsLabel = this->_gui.get<tgui::Label>("Gold");
		this->_armyLabel = this->_gui.get<tgui::Label>("Army");
		this->_foodLabel = this->_gui.get<tgui::Label>("Food");
		this->_passiveGoldsLabel = this->_gui.get<tgui::Label>("PassiveGold");
		this->_passiveArmyLabel = this->_gui.get<tgui::Label>("PassiveArmy");
		this->_passiveFoodLabel = this->_gui.get<tgui::Label>("PassiveFood");
		this->_nobilityHappinessLabel = this->_gui.get<tgui::Label>("NobilityHappiness");
		this->_peasantsHappinessLabel = this->_gui.get<tgui::Label>("PeasantsHappiness");
		this->_tradersHappinessLabel = this->_gui.get<tgui::Label>("TradersHappiness");
		this->_dialogs.showDialog(0, this->_state, this->_gui);
	}

	void InGameMenu::render()
	{
		this->_goldsLabel->setText(std::to_string(this->_state.gold));
		this->_armyLabel->setText(std::to_string(this->_state.army));
		this->_foodLabel->setText(std::to_string(this->_state.food));
		this->_passiveGoldsLabel->setText("+" + std::to_string(this->_state.passiveGold));
		this->_passiveArmyLabel->setText("+" + std::to_string(this->_state.passiveArmy));
		this->_passiveFoodLabel->setText("+" + std::to_string(this->_state.passiveFood));
		this->_nobilityHappinessLabel->setText(std::to_string(this->_state.nobilityHappiness));
		this->_peasantsHappinessLabel->setText(std::to_string(this->_state.peasantsHappiness));
		this->_tradersHappinessLabel->setText(std::to_string(this->_state.tradersHappiness));
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
