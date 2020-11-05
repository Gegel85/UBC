//
// Created by andgel on 15/10/2020.
//

#ifndef UBC_INGAMEMENU_HPP
#define UBC_INGAMEMENU_HPP


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"
#include "../QuestMgr.hpp"
#include "../Resources/GameState.hpp"

namespace UntilBeingCrowned
{
	class InGameMenu : public Menu {
	private:
		Resources &_res;
		tgui::Gui &_gui;
		MenuMgr &_mgr;
		QuestMgr &_questsMgr;
		GameState &_state;
		tgui::Label::Ptr _goldsLabel;
		tgui::Label::Ptr _armyLabel;
		tgui::Label::Ptr _foodLabel;
		tgui::Label::Ptr _passiveGoldsLabel;
		tgui::Label::Ptr _passiveArmyLabel;
		tgui::Label::Ptr _passiveFoodLabel;
		tgui::Label::Ptr _nobilityHappinessLabel;
		tgui::Label::Ptr _peasantsHappinessLabel;
		tgui::Label::Ptr _tradersHappinessLabel;

		void _hookHandlers();
		void _showQuestList(const std::vector<QuestMgr::Quest> &quests, const std::string &name);

	public:
		InGameMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs, GameState &state);
		~InGameMenu() override;
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_INGAMEMENU_HPP
