//
// Created by andgel on 18/11/2020.
//

#ifndef UBC_GAMEOVERMENU_HPP
#define UBC_GAMEOVERMENU_HPP


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "../Resources/GameState.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"

namespace UntilBeingCrowned
{
	class GameoverMenu : public Menu {
	private:
		MenuMgr &_mgr;
		tgui::Gui &_gui;
		GameState &_state;
		Resources &_res;

	public:
		GameoverMenu(MenuMgr &mgr, Resources &res, tgui::Gui &gui, GameState &state);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_GAMEOVERMENU_HPP
