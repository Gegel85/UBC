//
// Created by andgel on 14/11/2020.
//

#include <json.hpp>
#include <fstream>
#include <TGUI/TGUI.hpp>
#include "DialogMgr.hpp"
#include "Exceptions.hpp"

namespace UntilBeingCrowned
{
	DialogMgr::DialogMgr(tgui::Gui &gui) :
		_gui(gui)
	{
	}

	const std::map<std::string, std::string (DialogMgr::*)(const std::vector<std::string> &)> DialogMgr::_commands{
		{"",              &DialogMgr::_notImplemented},
		{"skip",          &DialogMgr::_skipCmd},
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

	void DialogMgr::update()
	{
		if (this->isDone() || this->_lineEnded || this->_onHold)
			return;

		auto &dialogMap = std::get<0>(this->_currentDialog);
		auto &dialog = std::get<1>(this->_currentDialog);
		auto &textPos = std::get<2>(this->_currentDialog);
		tgui::TextBox::Ptr textBox;

		if (this->_left)
			textBox = this->_gui.get<tgui::Panel>("otherPanel")->get<tgui::TextBox>("otherTextBox");
		else
			textBox = this->_gui.get<tgui::Panel>("myPanel")->get<tgui::TextBox>("myTextBox");

		char c = this->_dialogsString[dialogMap][dialog][textPos];

		if (c == '%') {
			auto cmd = DialogMgr::_parseCommand(textPos, this->_dialogsString[dialogMap][dialog]);

			try {
				this->_text += (this->*DialogMgr::_commands.at(cmd.first))(cmd.second);
			} catch (const std::exception &e) {
				this->_text += "Exception '" + getLastExceptionName() + "' thrown when trying to run command '";
				this->_text += cmd.first + "' (" + std::to_string(cmd.second.size()) + " argument(s)" + (cmd.second.empty() ? "" : ": ");
				for (size_t i = 0; i < cmd.second.size(); i++) {
					if (i)
						this->_text += ", ";
					this->_text += "'" + cmd.second[i] + "'";
				}
				this->_text += std::string(") : ") + e.what();
				this->_onHold = true;
			}
		} else
			this->_text += c;
		textPos++;
		textBox->setText(this->_text);
		this->_lineEnded = textPos >= this->_dialogsString[dialogMap][dialog].size();
	}

	void DialogMgr::startDialog(const std::string &id)
	{
		this->_done = this->_dialogsString[id].empty();
		if (this->_done)
			return;

		auto leftText = this->_gui.get<tgui::Panel>("otherPanel")->get<tgui::TextBox>("otherTextBox");
		auto rightText = this->_gui.get<tgui::Panel>("myPanel")->get<tgui::TextBox>("myTextBox");
		auto skipButton = this->_gui.get<tgui::Button>("Next");
		auto &dialogMap = std::get<0>(this->_currentDialog);
		auto &dialog = std::get<1>(this->_currentDialog);
		auto &textPos = std::get<2>(this->_currentDialog);

		leftText->setText("");
		rightText->setText("");
		for (int i = 0; i < 5; i++)
			this->_gui.get<tgui::Button>("Button" + std::to_string(i))->disconnectAll();
		dialogMap = id;
		dialog = 0;
		textPos = 1;
		this->_left = this->_dialogsString[dialogMap][dialog][0] == 'l';
		this->_onHold = false;
		this->_lineEnded = this->_dialogsString[id][0].empty();
		skipButton->disconnectAll();
		skipButton->connect("Clicked", &DialogMgr::clicked, this);
	}

	bool DialogMgr::isDone() const
	{
		return this->_done;
	}

	void DialogMgr::_nextLine()
	{
		auto &dialogMap = std::get<0>(this->_currentDialog);
		auto &dialog = std::get<1>(this->_currentDialog);
		auto &textPos = std::get<2>(this->_currentDialog);

		dialog++;
		this->_text = "";
		this->_done = dialog >= this->_dialogsString[dialogMap].size();
		if (!this->_done) {
			this->_lineEnded = this->_dialogsString[dialogMap][dialog].empty();
			this->_left = this->_dialogsString[dialogMap][dialog][0] == 'l';
			textPos = 1;
		}
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
				if (dialog.empty())
					throw InvalidDialogStringException("In dialog chunk '" + pair.first + "': The side character is missing (Empty dialog)");
				if (dialog[0] != 'l' && dialog[0] != 'r')
					throw InvalidDialogStringException("In dialog chunk '" + pair.first + "': The side character is missing (" + dialog[0] + " is not a valid side)");
				for (size_t pos = 1; pos < dialog.size(); pos++) {
					if (dialog[pos] == '%') {
						auto parsed  = DialogMgr::_parseCommand(pos, dialog);

						if (DialogMgr::_commands.find(parsed.first) == DialogMgr::_commands.end())
							throw InvalidDialogStringException("In dialog chunk '" + pair.first + "': Command '" + parsed.first + "' doesn't exist.");
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

	void DialogMgr::clicked()
	{
		if (this->isDone() || !this->_onHold)
			return;
		if (this->_lineEnded)
			this->_nextLine();
		else
			std::get<2>(this->_currentDialog) = this->_dialogsString[std::get<0>(this->_currentDialog)][std::get<1>(this->_currentDialog)].size();
	}

	bool DialogMgr::hasDialog(const std::string &id)
	{
		return this->_dialogsString.find(id) != this->_dialogsString.end();
	}

	std::string DialogMgr::_skipCmd(const std::vector<std::string> &)
	{
		this->_nextLine();
		return std::string();
	}
}