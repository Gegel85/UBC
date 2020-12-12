//
// Created by andgel on 17/11/2020.
//

#ifndef UBC_DIALOGMENU_HPP
#define UBC_DIALOGMENU_HPP


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/GameState.hpp"
#include "../DialogMgr.hpp"

namespace UntilBeingCrowned
{
	extern const std::vector<std::string> in_game_musics;

	class DialogMenu : public Menu {
	private:
		MenuMgr &_mgr;
		tgui::Gui &_gui;
		DialogMgr &_dialogMgr;
		GameState &_state;
		Resources &_res;

	public:
		DialogMenu(MenuMgr &mgr, Resources &res, tgui::Gui &gui, DialogMgr &dialogs, GameState &state);
		~DialogMenu() override;
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //UBC_DIALOGMENU_HPP
