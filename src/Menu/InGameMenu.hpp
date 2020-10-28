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
		QuestMgr &_dialogs;
		GameState &_state;

	public:
		InGameMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs, GameState &state);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_INGAMEMENU_HPP
