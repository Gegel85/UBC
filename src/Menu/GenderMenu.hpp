//
// Created by timcav on 10/11/2020.
//

#ifndef UBC_GENDERMENU_HPP
#define UBC_GENDERMENU_HPP

#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"
#include "../QuestMgr.hpp"

namespace UntilBeingCrowned {

	class GenderMenu : public Menu {
	private:
		Resources &_res;
		tgui::Gui &_gui;
		MenuMgr &_mgr;
		GameState &_state;
		QuestMgr &_quests;

		void _runGame(const std::string &flag);

	public:
		GenderMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, GameState &state, QuestMgr &quests);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_GENDERMENU_HPP
