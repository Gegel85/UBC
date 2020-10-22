//
// Created by andgel on 20/10/2020.
//

#ifndef UBC_DIALOGMGR_HPP
#define UBC_DIALOGMGR_HPP


#include <map>
#include <vector>
#include <string>
#include <TGUI/TGUI.hpp>
#include <json.hpp>
#include "Resources/Resources.hpp"

namespace UntilBeingCrowned
{
	class DialogMgr {
	private:
		unsigned pos = 0;
		std::pair<std::string, unsigned> _selected;
		tgui::ScrollablePanel::Ptr _panel;
		std::map<std::string, tgui::Picture::Ptr> _pictures;
		std::map<std::string, std::vector<nlohmann::json>> _dialogs;
		std::function<void (nlohmann::json dialog, unsigned buttonId, const std::string &file, unsigned id)> _onClickButton;

	public:
		DialogMgr();
		void onClick(const std::function<void (nlohmann::json dialog, unsigned buttonId, const std::string &file, unsigned id)> &handler);
		void loadFile(const std::string &path, Resources &resources);
		void update(Resources &);
		void showDialog(const std::string &file, unsigned id, tgui::Gui &gui);
	};
}


#endif //UBC_DIALOGMGR_HPP
