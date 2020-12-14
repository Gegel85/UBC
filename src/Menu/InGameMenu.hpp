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
#include "../Resources/State.hpp"

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
		tgui::Label::Ptr _goldPassiveLabel;
		tgui::Label::Ptr _armyPassiveLabel;
		tgui::Label::Ptr _foodPassiveLabel;

		void _nextWeek();
		void _hookHandlers();
		void _showQuestList(const std::vector<std::shared_ptr<QuestMgr::Quest>> &quests, const std::string &name);
		void _saveAndQuit();

	public:
		InGameMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs, GameState &state);
		~InGameMenu() override;
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_INGAMEMENU_HPP
