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
#include "Resources/GameState.hpp"

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

			bool canApply(const GameState &state) const;
			void apply(GameState &state) const;
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
			std::pair<int, int> tradersHappinessRequirement;
			std::pair<int, int> peasantsHappinessRequirement;
			std::pair<int, int> nobilityHappinessRequirement;

			bool isUnlocked(const GameState &state) const;
			Quest(const nlohmann::json &json, std::map<std::string, sf::Texture> &textures);
		};

		struct ClickEvent {
			const Quest &quest;
			unsigned buttonId;
			unsigned id;
		};

	private:
		std::vector<Quest> _newQuests;
		std::vector<Quest> _unlockedQuests;
		unsigned _selected;
		tgui::ScrollablePanel::Ptr _panel;
		std::vector<Quest> _quests;
		std::function<void (const ClickEvent &event)> _onClickButton;

	public:
		QuestMgr();
		void onClick(const std::function<void (const ClickEvent &event)> &handler);
		void loadFile(const std::string &path, Resources &resources);
		std::vector<Quest> getUnlockedQuests();
		std::vector<Quest> getNewQuests();
		void nextWeek(GameState &state);
		void showDialog(unsigned id, GameState &state, tgui::Gui &gui);
	};
}


#endif //UBC_QUESTMGR_HPP
