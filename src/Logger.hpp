//
// Created by Gegel85 on 15/01/2019.
//

#ifndef UBC_LOGGER_HPP
#define UBC_LOGGER_HPP


#include <fstream>
#include <string>

namespace UntilBeingCrowned
{
	//! @brief Used to log messages
	class Logger {
	public:
		//! @brief The levels of logging available
		enum LogLevel {
			LOG_DEBUG,
			LOG_INFO,
			LOG_WARNING,
			LOG_ERROR,
			LOG_CRITICAL,
			LOG_NONE,
		};

		//! @param filepath The path to the file to log to
		//! @param level The minimum logging level to display
		explicit Logger(const std::string &filepath = "./latest.log", LogLevel level = LOG_INFO) noexcept;
		~Logger() noexcept;

		//! @brief Logs a message in the console and the log file
		//! @param content The message to log
		//! @param prepend String prepended to the message
		void msg(const std::string &content, const std::string &prepend = "") noexcept;

		//! @brief Logs a message as log level DEBUG
		//! @param content The message to log
		void debug(const std::string &content) noexcept;

		//! @brief Logs a message as log level INFO
		//! @param content The message to log
		void info(const std::string &content) noexcept;

		//! @brief Logs a message as log level WARNING
		//! @param content The message to log
		void warn(const std::string &content) noexcept;

		//! @brief Logs a message as log level ERROR
		//! @param content The message to log
		void error(const std::string &content) noexcept;

		//! @brief Logs a message as log level FATAL
		//! @param content The message to log
		void fatal(const std::string &content) noexcept;

	private:
		//! @brief The file stream to log to
		std::ofstream _file;

		//! @brief The minimum logging level
		LogLevel _level;
	};
}


#endif //UBC_LOGGER_HPP
