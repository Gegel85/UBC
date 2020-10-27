//
// Created by andgel on 20/10/2020.
//

#ifndef UBC_QUESTMGR_HPP
#define UBC_QUESTMGR_HPP


#include <map>
#include <vector>
#include <string>
#include <TGUI/TGUI.hpp>
#include <json.hpp>
#include "Resources/Resources.hpp"

namespace UntilBeingCrowned
{
	class QuestMgr {
	public:
		struct Effect {
			std::vector<std::string> setFlags;
			std::vector<std::string> unsetFlags;
			int goldChange;
			int foodChange;
			int armyChange;
			int passiveGoldChange;
			int passiveFoodChange;
			int passiveArmyChange;
			int peasantsHappiness;
			int tradersHappiness;
			int nobilityHappiness;

			Effect(const nlohmann::json &json);
		};

		struct Quest {
			tgui::Picture::Ptr pic;
			std::string title;
			std::string description;
			std::vector<std::string> buttons;
			std::vector<std::string> requirements;
			std::pair<unsigned, unsigned> weekRange;
			std::vector<Effect> buttons_effects;
			std::pair<unsigned, unsigned> tradersHappinessRequirement;
			std::pair<unsigned, unsigned> peasantsHappinessRequirement;
			std::pair<unsigned, unsigned> nobilityHappinessRequirement;

			Quest(const nlohmann::json &json, std::map<std::string, sf::Texture> &textures);
		};

		struct ClickEvent {
			const Quest &quest;
			unsigned buttonId;
			const std::string &file;
			unsigned id;
		};

	private:
		std::pair<std::string, unsigned> _selected;
		tgui::ScrollablePanel::Ptr _panel;
		std::map<std::string, std::vector<Quest>> _dialogs;
		std::function<void (const ClickEvent &event)> _onClickButton;

	public:
		QuestMgr();
		void onClick(const std::function<void (const ClickEvent &event)> &handler);
		void loadFile(const std::string &path, Resources &resources);
		void update(Resources &);
		void showDialog(const std::string &file, unsigned id, tgui::Gui &gui);
	};
}


#endif //UBC_QUESTMGR_HPP
