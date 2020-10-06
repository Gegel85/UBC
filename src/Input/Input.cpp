//
// Created by Gegel85 on 28/09/2019.
//

#include "Input.hpp"

namespace UntilBeingCrowned
{
	std::string Input::actionToString(UntilBeingCrowned::Input::Action action)
	{
		switch (action) {
		case UP:
			return "Up";
		case RIGHT:
			return "Right";
		case DOWN:
			return "Down";
		case LEFT:
			return "Left";
		case SKIP_DIALOG:
			return "Skip dialog";
		case ADVANCE_DIALOG:
			return "Advance dialog";
		default:
			return "??";
		}
	}

	Input::Event::Event(UntilBeingCrowned::Input::Event::Type type, UntilBeingCrowned::Input::Action action) :
		type(type),
		action(action)
	{
	}
}