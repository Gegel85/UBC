//
// Created by andgel on 28/10/2020.
//

#ifndef UBC_GAMESTATE_HPP
#define UBC_GAMESTATE_HPP


namespace UntilBeingCrowned
{
	struct GameState {
		int gold;
		int army;
		int food;
		int passiveGold;
		int passiveArmy;
		int passiveFood;
		int peasantsHappiness;
		int tradersHappiness;
		int nobilityHappiness;
		unsigned week;
	};
}


#endif //UBC_GAMESTATE_HPP
