//
// Created by andgel on 08/10/2020.
//

#include "Logger.hpp"

namespace UntilBeingCrowned
{
	Logger logger{
		"latest.log",
	#ifdef _DEBUG
		Logger::LOG_DEBUG
	#else
		Logger::LOG_DEBUG
	#endif
	};
}