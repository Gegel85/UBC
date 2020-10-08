//
// Created by Gegel85 on 22/12/2019.
//

#ifndef UBC_MENU_EXCEPTIONS_HPP
#define UBC_MENU_EXCEPTIONS_HPP


#include <exception>
#include <string>
#include "../Exceptions.hpp"

namespace UntilBeingCrowned
{
	class InvalidMenuException : public BaseException {
	public:
		InvalidMenuException(const std::string &&msg) : BaseException(static_cast<const std::string &&>(msg)) {};
	};
}


#endif //UBC_MENU_EXCEPTION_HPP
