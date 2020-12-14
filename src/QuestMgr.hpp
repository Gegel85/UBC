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
		private:
			unsigned _id;

		public:
			const sf::Texture &pic;
			std::string title;
			std::string description;
			std::vector<std::string> buttons;
			std::vector<std::string> requirements;
			std::pair<unsigned, unsigned> weekRange;
			std::vector<Effect> buttons_effects;
			std::pair<int, int> tradersHappinessRequirement;
			std::pair<int, int> peasantsHappinessRequirement;
			std::pair<int, int> nobilityHappinessRequirement;
			bool forceOpen;

			unsigned int getId() const;
			bool isUnlocked(const GameState &state) const;
			bool operator==(const Quest &other) const;
			Quest(unsigned id, const nlohmann::json &json, const std::map<std::string, sf::Texture> &textures);
		};

		struct ClickEvent {
			const Quest &quest;
			unsigned buttonId;
			unsigned id;
		};

	private:
		std::vector<std::shared_ptr<Quest>> _newQuests;
		std::vector<std::shared_ptr<Quest>> _unlockedQuests;
		unsigned _selected;
		std::vector<tgui::Button::Ptr> _buttons;
		tgui::ScrollablePanel::Ptr _panel;
		std::vector<bool> _usedQuests;
		std::vector<std::shared_ptr<Quest>> _quests;
		std::function<void (const ClickEvent &event)> _onClickButton;
		GameState &_state;
		bool _continued = false;

		void _addNewUnlockedQuests();
		void _checkJsonValidity(const nlohmann::json &json, const std::map<std::string, sf::Texture> &textures);

	public:
		QuestMgr(GameState &state);
		void onClick(const std::function<void (const ClickEvent &event)> &handler);
		void loadFile(const std::string &path, Resources &resources);
		std::vector<std::shared_ptr<Quest>> getUnlockedQuests();
		std::vector<std::shared_ptr<Quest>> getNewQuests();
		void nextWeek();
		void reset();
		void showDialog(unsigned id, tgui::Gui &gui);
		std::string serializedUsedQuests();
		std::string serializedNewQuests();
		std::vector<std::shared_ptr<Quest>> const &getQuests() const;
		void setUsedQuests(std::vector<bool>);
		void setNewQuests(std::vector<std::shared_ptr<Quest>> q);
	};
}


#endif //UBC_QUESTMGR_HPP
