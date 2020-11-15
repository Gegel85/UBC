//
// Created by andgel on 14/11/2020.
//

#include <json.hpp>
#include <fstream>
#include "DialogMgr.hpp"
#include "Exceptions.hpp"

namespace UntilBeingCrowned
{
	const std::map<std::string, std::string (DialogMgr::*)(const std::vector<std::string> &)> DialogMgr::_commands{
		{"",              &DialogMgr::_notImplemented},
		{"skip",          &DialogMgr::_notImplemented},
		{"setMusic",      &DialogMgr::_notImplemented},
		{"playSfx",       &DialogMgr::_notImplemented},
		{"setSprite",     &DialogMgr::_notImplemented},
		{"setSpriteRect", &DialogMgr::_notImplemented},
		{"finish",        &DialogMgr::_notImplemented},
		{"choices",       &DialogMgr::_notImplemented},
		{"setFlag",       &DialogMgr::_notImplemented},
		{"unsetFlag",     &DialogMgr::_notImplemented},
		{"wait",          &DialogMgr::_notImplemented},
	};

	void DialogMgr::update(tgui::Gui &gui)
	{
		if (this->isDone())
			return;

		auto &dialogMap = std::get<0>(this->_currentDialog);
		auto &dialog = std::get<1>(this->_currentDialog);
		auto &textPos = std::get<2>(this->_currentDialog);

		textPos++;
	}

	void DialogMgr::startDialog(tgui::Gui &gui)
	{

	}

	bool DialogMgr::isDone() const
	{
		return this->_done;
	}

	void DialogMgr::_nextLine()
	{
		auto &dialogMap = std::get<0>(this->_currentDialog);
		auto &dialog = std::get<1>(this->_currentDialog);

		dialog++;
		this->_done = dialog >= this->_dialogsString[dialogMap].size();
	}

	void DialogMgr::loadFile(const std::string &path)
	{
		std::ifstream stream{path};
		nlohmann::json json;

		if (stream.fail())
			throw FileNotFoundException(reinterpret_cast<const std::string &&>(path));
		stream >> json;
		stream.close();

		if (!json.is_object())
			throw InvalidDialogFileException("Dialog file doesn't contain an object");

		this->_dialogsString = json.get<std::map<std::string, std::vector<std::string>>>();
		for (const auto &pair : this->_dialogsString) {
			for (const auto &dialog : pair.second) {
				for (size_t pos = 0; pos < dialog.size(); pos++) {
					if (dialog[pos] == '%') {
						auto parsed  = this->_parseCommand(pos, dialog);

						if (DialogMgr::_commands.find(parsed.first) == DialogMgr::_commands.end())
							throw InvalidDialogStringException("Command '" + parsed.first + "' doesn't exist.");
					}
				}
			}
		}
	}

	std::pair<std::string, std::vector<std::string>> DialogMgr::_parseCommand(size_t &pos, const std::string &cmdStart)
	{
		std::string command;
		std::string token;
		std::vector<std::string> args;
		size_t strStart = 0;
		size_t start = pos;
		char sep = 0;

		++pos;
		while (pos < cmdStart.size() && (sep || cmdStart[pos] != '%')) {
			if (cmdStart[pos] == '\'' || cmdStart[pos] == '"') {
				if (!sep) {
					sep = cmdStart[pos];;
					strStart = pos;
				} else if (cmdStart[pos] == sep)
					sep = 0;
			} else if (std::isspace(cmdStart[pos])) {
				if (!token.empty()) {
					if (command.empty())
						command = token;
					else
						args.push_back(token);
					token.clear();
				}
			} else
				token += cmdStart[pos];
			++pos;
		}

		if (sep)
			throw UnfinishedStringLiteralException("Unfinished command in string '" + cmdStart.substr(strStart) + "'");

		if (cmdStart[pos] != '%')
			throw UnfinishedCommandException("Unfinished command near string '" + cmdStart.substr(start) + "'");

		return {
			command,
			args
		};
	}

	std::string DialogMgr::_notImplemented(const std::vector<std::string> &)
	{
		throw NotImplementedException();
	}
}