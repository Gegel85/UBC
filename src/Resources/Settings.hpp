//
// Created by andgel on 13/10/2020.
//

#ifndef UBC_SETTINGS_HPP
#define UBC_SETTINGS_HPP


#include "../Input/Input.hpp"

namespace UntilBeingCrowned
{
	struct Settings {
		//! @brief The current music volume
		float musicVolume;

		//! @brief The current sound effect volume
		float sfxVolume;

		//! @brief The current state of fullscreen of the window
		bool fullscreen;

		//! @brief The current input
		std::unique_ptr<Input> input;
	};
}


#endif //UBC_SETTINGS_HPP
