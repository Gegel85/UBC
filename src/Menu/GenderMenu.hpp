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
		QuestMgr &_dialogs;

		std::string _nexLevel;

	public:
		GenderMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;

		void launchAsGirl();
		void launchAsBoy();

	private:

		static void girlButtonHandler(GenderMenu &m);
		static void boyButtonHandler(GenderMenu &m);
	};
}


#endif //UBC_GENDERMENU_HPP
