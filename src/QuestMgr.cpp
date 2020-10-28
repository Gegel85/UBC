//
// Created by andgel on 20/10/2020.
//

#include <filesystem>
#include <iostream>
#include "QuestMgr.hpp"
#include "Exceptions.hpp"
#include "Resources/Game.hpp"

namespace UntilBeingCrowned
{
	QuestMgr::QuestMgr()
	{
		this->_panel = tgui::ScrollablePanel::create({600, 700});
		this->_panel->setPosition("&.w / 2 - w / 2", "&.h / 2 - h / 2");
		this->_panel->loadWidgetsFromFile("gui/quest.gui");
	}

	void QuestMgr::loadFile(const std::string &path, Resources &resources)
	{
		std::ifstream stream{path};
		nlohmann::json val;

		if (!stream)
			throw InvalidQuestFileException("Cannot open " + path + ": " + strerror(errno));

		stream >> val;
		if (!val.is_array())
			throw InvalidQuestFileException("File is expected to contain an array of objects");
		if (val.empty())
			throw InvalidQuestFileException("Array is empty");
		for (size_t i = 0; i < val.size(); i++) {
			const auto &v = val[i];

			if (!v.is_object())
				throw InvalidQuestFileException(i, "Element in array is not an object");
			if (!v.contains("title") || !v["title"].is_string())
				throw InvalidQuestFileException(i, "title field is not a string");
			if (!v.contains("description") || !v["description"].is_string())
				throw InvalidQuestFileException(i, "description field is not a string");
			if (!v.contains("picture") || !v["picture"].is_string())
				throw InvalidQuestFileException(i, "picture field is not a string");
			if (!v.contains("buttons") || !v["buttons"].is_array())
				throw InvalidQuestFileException(i, "button field is not an array");
			for (const auto &k : v["buttons"])
				if (!k.is_string())
					throw InvalidQuestFileException(i, "button field contains a non string element");

			if (!v.contains("requirements") || !v["requirements"].is_array())
				throw InvalidQuestFileException(i, "requirements field is not an array");
			for (const auto &k : v["requirements"])
				if (!k.is_string())
					throw InvalidQuestFileException(i, "requirements field contains a non string element");
			if (!v.contains("week_no") || !v["week_no"].is_number_unsigned())
				throw InvalidQuestFileException(i, "week_no field is not an unsigned integer");
			if (!v.contains("happiness_requirement") || !v["happiness_requirement"].is_object())
				throw InvalidQuestFileException(i, "happiness_requirement field is not an object");
			if (!v["happiness_requirement"].contains("traders") || !v["happiness_requirement"]["traders"].is_object())
				throw InvalidQuestFileException(i, "happiness_requirement.traders field is not an object");
			if (!v["happiness_requirement"].contains("nobility") || !v["happiness_requirement"]["nobility"].is_object())
				throw InvalidQuestFileException(i, "happiness_requirement.nobility field is not an object");
			if (!v["happiness_requirement"].contains("peasants") || !v["happiness_requirement"]["peasants"].is_object())
				throw InvalidQuestFileException(i, "happiness_requirement.peasants field is not an object");

			if (!v["happiness_requirement"]["traders" ].contains("min") || !v["happiness_requirement"]["traders"]["min"].is_number_integer())
				throw InvalidQuestFileException(i, "happiness_requirement.traders.min field is not an integer");
			if (!v["happiness_requirement"]["traders" ].contains("max") || !v["happiness_requirement"]["traders"]["max"].is_number_integer())
				throw InvalidQuestFileException(i, "happiness_requirement.traders.max field is not an integer");
			if (!v["happiness_requirement"]["nobility"].contains("min") || !v["happiness_requirement"]["nobility"]["min"].is_number_integer())
				throw InvalidQuestFileException(i, "happiness_requirement.nobility.min field is not an integer");
			if (!v["happiness_requirement"]["nobility"].contains("max") || !v["happiness_requirement"]["nobility"]["max"].is_number_integer())
				throw InvalidQuestFileException(i, "happiness_requirement.nobility.max field is not an integer");
			if (!v["happiness_requirement"]["peasants"].contains("min") || !v["happiness_requirement"]["peasants"]["min"].is_number_integer())
				throw InvalidQuestFileException(i, "happiness_requirement.peasants.min field is not an integer");
			if (!v["happiness_requirement"]["peasants"].contains("max") || !v["happiness_requirement"]["peasants"]["max"].is_number_integer())
				throw InvalidQuestFileException(i, "happiness_requirement.peasants.max field is not an integer");

			if (!v.contains("happiness_requirement") || !v["happiness_requirement"].is_object())
				throw InvalidQuestFileException(i, "happiness_requirement field is not an object");
			if (!v.contains("expire_time") || !v["expire_time"].is_number_integer())
				throw InvalidQuestFileException(i, "expire_time field is not an integer");
			if (!v.contains("buttons_effects") || !v["buttons_effects"].is_array())
				throw InvalidQuestFileException(i, "requirements field is not an array");
			for (size_t j = 0; j < v["buttons_effects"].size(); j++) {
				const auto &k = v["buttons_effects"][j];

				if (!k.is_object())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": buttons_effects field contains a non object element");
				if (!k.contains("gold") || !k["gold"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": gold field is not an integer");
				if (!k.contains("food") || !k["food"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": food field is not an integer");
				if (!k.contains("army") || !k["army"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": army field is not an integer");
				if (!k.contains("passive_gold") || !k["passive_gold"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": passive_gold field is not an integer");
				if (!k.contains("passive_food") || !k["passive_food"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": passive_food field is not an integer");
				if (!k.contains("passive_army") || !k["passive_army"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": passive_army field is not an integer");
				if (!k.contains("peasants_happiness") || !k["peasants_happiness"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": peasants_happiness field is not an integer");
				if (!k.contains("nobility_happiness") || !k["nobility_happiness"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": nobility_happiness field is not an integer");
				if (!k.contains("traders_happiness") || !k["traders_happiness"].is_number_integer())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": traders_happiness field is not an integer");
				if (!k.contains("set_flags") || !k["set_flags"].is_array())
					throw InvalidQuestFileException(i, "In effect #"+ std::to_string(j) +": set_flags field is not an array");
				for (auto &f : k["set_flags"])
					if (!f.is_string())
						throw InvalidQuestFileException(
							i, "In effect #"+ std::to_string(j) +
							": set_flags field contains a non string element"
						);
				if (!k.contains("unset_flags") || !k["unset_flags"].is_array())
					throw InvalidQuestFileException(i, "unset_flags field is not an array");
				for (auto &f : k["unset_flags"])
					if (!f.is_string())
						throw InvalidQuestFileException(
							i, "In effect #"+ std::to_string(j) +
							   ": unset_flags field contains a non string element"
						);
			}
		}

		for (const auto &v : val)
			this->_quests.emplace_back(v, resources.textures);
		stream.close();
	}

	void QuestMgr::showDialog(unsigned int id, GameState &state, tgui::Gui &gui)
	{
		auto panel = tgui::Panel::create({"100%", "100%"});
		unsigned y = 0;
		unsigned index = 0;
		auto &val = this->_quests.at(id);
		int size = val.buttons.size();
		double ysize = (60 - (size - 1) / 3 * 10) / ((size - 1) / 3 + 1.);
		auto title = this->_panel->get<tgui::Label>("Title");
		auto desc = this->_panel->get<tgui::TextBox>("TextBox1");
		auto fct = [this, &val, id, &gui, panel](unsigned butId) {
			if (this->_onClickButton)
				this->_onClickButton({val, butId, id});
			gui.remove(this->_panel);
			gui.remove(panel);
		};

		this->_selected = id;
		title->setText(val.title);
		desc->setText(val.description);
		desc->setVerticalScrollbarValue(0);
		this->_panel->add(val.pic);
		for (int left = size; left > 0; left -= 3, y++) {
			auto start = left > 3 ? 3 : left;
			auto xsize = (500 - (start - 1) * 10.) / start;

			for (unsigned i = start; i; i--) {
				auto but = tgui::Button::create(val.buttons[index]);
				auto *renderer = but->getRenderer();

				if (index < val.buttons_effects.size() && !val.buttons_effects[index].canApply(state))
					but->setEnabled(false);

				renderer->setBorders({0, 0, 0, 0});
				renderer->setBackgroundColor("transparent");
				renderer->setBackgroundColorDisabled("transparent");
				renderer->setBackgroundColorHover("#FFFFFF1F");
				renderer->setBackgroundColorDown("#FFFFFF2E");
				renderer->setFont("assets/kenpixel.ttf");
				but->setTextSize(16);
				but->setSize(xsize, ysize);
				but->setPosition(index % 3 * (xsize + 10) + 50, index / 3 * (ysize + 10) + 580);
				but->connect("clicked", fct, index);
				index++;
				this->_panel->add(but);
			}
		}
		panel->getRenderer()->setBackgroundColor({0, 0, 0, 175});
		gui.add(panel);
		gui.add(this->_panel);
	}

	void QuestMgr::onClick(const std::function<void(const ClickEvent &event)> &handler)
	{
		this->_onClickButton = handler;
	}

	std::vector<QuestMgr::Quest> QuestMgr::getUnlockedQuests()
	{
		return this->_unlockedQuests;
	}

	std::vector<QuestMgr::Quest> QuestMgr::getNewQuests()
	{
		return this->_newQuests;
	}

	void QuestMgr::nextWeek(GameState &state)
	{
		this->_newQuests.clear();
	}

	QuestMgr::Quest::Quest(const nlohmann::json &json, std::map<std::string, sf::Texture> &textures) :
		pic(tgui::Picture::create(textures[json["picture"]])),
		title(json["title"]),
		description(json["description"]),
		buttons(json["buttons"]),
		requirements(json["requirements"]),
		weekRange(json["week_no"], json["expire_time"]),
		buttons_effects(json["buttons_effects"].begin(), json["buttons_effects"].end()),
		tradersHappinessRequirement(json["happiness_requirement"]["traders"]["min"], json["happiness_requirement"]["traders"]["max"]),
		peasantsHappinessRequirement(json["happiness_requirement"]["peasants"]["min"], json["happiness_requirement"]["peasants"]["max"]),
		nobilityHappinessRequirement(json["happiness_requirement"]["nobility"]["min"], json["happiness_requirement"]["nobility"]["max"])
	{
		this->weekRange.second += this->weekRange.first;
		this->pic->setSize(150, 150);
		this->pic->setPosition(390, 50);
	}

	bool QuestMgr::Quest::isUnlocked(const GameState &state) const
	{
		for (const auto &elem : this->requirements)
			if (std::find(state.flags.begin(), state.flags.end(), elem) == state.flags.end())
				return false;

		return this->weekRange.first <= state.week &&
		       state.week < this->weekRange.second &&

		       this->nobilityHappinessRequirement.first <= state.nobilityHappiness &&
		       state.nobilityHappiness <= this->nobilityHappinessRequirement.second &&

		       this->peasantsHappinessRequirement.first <= state.peasantsHappiness &&
		       state.peasantsHappiness <= this->peasantsHappinessRequirement.second &&

		       this->tradersHappinessRequirement.first <= state.tradersHappiness &&
		       state.tradersHappiness <= this->tradersHappinessRequirement.second;
	}

	QuestMgr::Effect::Effect(const nlohmann::json &json) :
		setFlags(json["set_flags"]),
		unsetFlags(json["unset_flags"]),
		goldChange(json["gold"]),
		foodChange(json["food"]),
		armyChange(json["army"]),
		passiveGoldChange(json["passive_gold"]),
		passiveFoodChange(json["passive_food"]),
		passiveArmyChange(json["passive_army"]),
		peasantsHappiness(json["peasants_happiness"]),
		tradersHappiness(json["traders_happiness"]),
		nobilityHappiness(json["nobility_happiness"])
	{
	}

	bool QuestMgr::Effect::canApply(const GameState &state) const
	{
		return state.gold + this->goldChange >= 0 &&
		       state.army + this->armyChange >= 0 &&
		       state.food + this->foodChange >= 0 &&
		       state.passiveGold + this->passiveGoldChange >= 0 &&
		       state.passiveArmy + this->passiveArmyChange >= 0 &&
		       state.passiveFood + this->passiveFoodChange >= 0;
	}

	void QuestMgr::Effect::apply(GameState &state) const
	{
		state.gold              += this->goldChange;
		state.army              += this->armyChange;
		state.food              += this->foodChange;
		state.passiveGold       += this->passiveGoldChange;
		state.passiveArmy       += this->passiveArmyChange;
		state.passiveFood       += this->passiveFoodChange;
		state.peasantsHappiness += this->peasantsHappiness;
		state.tradersHappiness  += this->tradersHappiness;
		state.nobilityHappiness += this->nobilityHappiness;

		for (auto &flag : this->setFlags)
			state.flags.push_back(flag);
		for (auto &flag : this->unsetFlags)
			state.flags.erase(std::remove(state.flags.begin(), state.flags.end(), flag), state.flags.end());
	}
}