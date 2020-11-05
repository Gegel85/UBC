//
// Created by andgel on 13/10/2020.
//

#ifndef UBC_STATE_HPP
#define UBC_STATE_HPP


#include <TGUI/TGUI.hpp>
#include "../QuestMgr.hpp"
#include "../Menu/MenuMgr.hpp"
#include "Settings.hpp"
#include "GameState.hpp"

namespace UntilBeingCrowned
{
	struct State {
		tgui::Gui gui;
		MenuMgr menuMgr;
		Settings settings;
		QuestMgr questMgr;
		GameState game;

		State() : questMgr(this->game) {};
	};
}


#endif //UBC_STATE_HPP
