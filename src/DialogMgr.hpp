//
// Created by andgel on 14/11/2020.
//

#ifndef UBC_DIALOGMGR_HPP
#define UBC_DIALOGMGR_HPP

#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <TGUI/Gui.hpp>

namespace UntilBeingCrowned
{
	class DialogMgr {
	private:
		static const std::map<std::string, std::string (DialogMgr::*)(const std::vector<std::string> &)> _commands;
		std::map<std::string, std::vector<std::string>> _dialogsString;
		std::tuple<std::string, unsigned, size_t> _currentDialog = {"", 0, 0};
		unsigned _waitingTime = 0;
		bool _done = true;
		bool _lineEnded = false;

		std::string _notImplemented(const std::vector<std::string> &args);
		void _nextLine();
		std::pair<std::string, std::vector<std::string>> _parseCommand(size_t &pos, const std::string &cmdStart);

	public:
		bool isDone() const;
		void update(tgui::Gui &gui);
		void startDialog(tgui::Gui &gui);
		void loadFile(const std::string &path);
	};
}


#endif //UBC_DIALOGMGR_HPP
