//
// Created by andgel on 13/10/2020.
//

#ifndef UBC_GAME_HPP
#define UBC_GAME_HPP


#include "State.hpp"
#include "Resources.hpp"

namespace UntilBeingCrowned
{
	struct Game {
		State state;
		Resources resources;

		Game() : state(this->resources) {};
	};
}


#endif //UBC_GAME_HPP
