//
// Created by timcav on 28/10/2020.
//

#ifndef UBC_OPTIONMENU_HPP
#define UBC_OPTIONMENU_HPP


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"
#include "../QuestMgr.hpp"

namespace UntilBeingCrowned
{
	class OptionMenu : public Menu {
	private:
		Resources &_res;
		tgui::Gui &_gui;
		MenuMgr &_mgr;
		QuestMgr &_dialogs;

	public:
		OptionMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;

		void backButton();

    private:
        static void backButtonHandler(OptionMenu &);

    };
}



#endif //UBC_OPTIONMENU_HPP
