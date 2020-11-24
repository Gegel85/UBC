//
// Created by andgel on 28/10/2020.
//

#ifndef UBC_GAMESTATE_HPP
#define UBC_GAMESTATE_HPP


namespace UntilBeingCrowned
{
	struct GameState {
		int gold = 0;
		int army = 0;
		int food = 0;
		int goldPassive = 0;
		int armyPassive = 0;
		int foodPassive = 0;
		int foodHappiness = 0;
		int goldHappiness = 0;
		int armyHappiness = 0;
		std::vector<std::string> flags;
		unsigned week;
	};
}


#endif //UBC_GAMESTATE_HPP
