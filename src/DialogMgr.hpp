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
		std::map<std::string, tgui::Picture::Ptr> _pictures;
		std::map<std::string, std::vector<nlohmann::json>> _dialogs;

		tgui::Panel::Ptr _makePanel(const std::string &file, unsigned id);
	public:
		DialogMgr() = default;
		void loadFile(const std::string &path, Resources &resources);
		void update(Resources &);
		void showDialog(const std::string &file, unsigned id, tgui::Gui &gui);
	};
}


#endif //UBC_DIALOGMGR_HPP
