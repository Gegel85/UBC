//
// Created by andgel on 18/11/2020.
//

#ifndef UBC_VICTORYMENU_HPP
#define UBC_VICTORYMENU_HPP


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "../Resources/GameState.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"

namespace UntilBeingCrowned
{
	class VictoryMenu : public Menu {
	private:
		MenuMgr &_mgr;
		tgui::Gui &_gui;
		GameState &_state;
		Resources &_res;

	public:
		VictoryMenu(MenuMgr &mgr, Resources &res, tgui::Gui &gui, GameState &state);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_VICTORYMENU_HPP
