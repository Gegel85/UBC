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

	public:
		MainMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}



#endif //UBC_MAINMENU_H
