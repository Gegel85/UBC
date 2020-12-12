//
// Created by timcav on 28/10/2020.
//

#ifndef UBC_LOADINGMENU_HPP
#define UBC_LOADINGMENU_HPP



#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"
#include "../QuestMgr.hpp"

namespace UntilBeingCrowned
{
	class LoadingMenu : public Menu {
	private:
		tgui::Gui &_gui;
		MenuMgr &_mgr;
		Resources &_res;

		void _backButton();

	public:
		LoadingMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_LOADINGMENU_HPP
