//
// Created by timcav on 27/10/2020.
//

#ifndef UBC_MAINMENU_H
#define UBC_MAINMENU_H


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"
#include "../QuestMgr.hpp"

namespace UntilBeingCrowned
{
	class MainMenu : public Menu {
	private:
		Resources &_res;
		tgui::Gui &_gui;
		MenuMgr &_mgr;
		QuestMgr &_dialogs;

	public:
		MainMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;

		void newGameButton();
		void loadGameButton();
		void optionsButton();
		void exitButton();

	private:
		static void newGameButtonHandler(MainMenu &m);
		static void loadGameButtonHandler(MainMenu &m);
		static void optionsButtonHandler(MainMenu &m);
		static void exitButtonHandler(MainMenu &m);

	};
}



#endif //UBC_MAINMENU_H
