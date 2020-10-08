//
// Created by Gegel85 on 22/12/2019.
//

#ifndef UBC_MENU_HPP
#define UBC_MENU_HPP


#include "../Input/Input.hpp"

namespace UntilBeingCrowned
{
	class Menu {
	public:
		virtual void switched(bool isActive) = 0;
		virtual void render() = 0;
		virtual void handleEvent(const Input::Event &event) = 0;
	};
}


#endif //UBC_MENU_HPP
