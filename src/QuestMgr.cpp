//
// Created by andgel on 20/10/2020.
//

#include <fstream>
#include <filesystem>
#include <iostream>
#include "QuestMgr.hpp"
#include "Exceptions.hpp"

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

		if (!stream)
			throw InvalidDialogFileException("Cannot open " + path + ": " + strerror(errno));

		nlohmann::json val;
		std::string name = std::filesystem::path(path).filename().string();

		stream >> val;
#ifdef _DEBUG
		if (!val.is_array())
			throw InvalidDialogFileException("File is expected to contain an array of objects");
		if (val.empty())
			throw InvalidDialogFileException("Array is empty");
		for (size_t i = 0; i < val.size(); i++) {
			const auto &v = val[i];

			if (!v.is_object())
				throw InvalidDialogFileException(i, "Element in array is not an object");
			if (!v.contains("expire_time") || !v["title"].is_string())
				throw InvalidDialogFileException(i, "title field is not a string");
			if (!v.contains("expire_time") || !v["description"].is_string())
				throw InvalidDialogFileException(i, "description field is not a string");
			if (!v.contains("expire_time") || !v["picture"].is_string())
				throw InvalidDialogFileException(i, "picture field is not a string");
			if (!v.contains("buttons") || !v["buttons"].is_array())
				throw InvalidDialogFileException(i, "button field is not an array");
			for (const auto &k : v["buttons"])
				if (!k.is_string())
					throw InvalidDialogFileException(i, "button field contains a non string element");

			if (!v.contains("requirements") || !v["requirements"].is_array())
				throw InvalidDialogFileException(i, "requirements field is not an array");
			for (const auto &k : v["requirements"])
				if (!k.is_string())
					throw InvalidDialogFileException(i, "requirements field contains a non string element");
			if (!v.contains("expire_time") || !v["week_no"].is_number_unsigned())
				throw InvalidDialogFileException(i, "week_no field is not an unsigned integer");
			if (!v.contains("expire_time") || !v["expire_time"].is_number_integer())
				throw InvalidDialogFileException(i, "expire_time field is not an integer");
			if (!v.contains("buttons_effects") || !v["buttons_effects"].is_array())
				throw InvalidDialogFileException(i, "requirements field is not an array");
			for (const auto &k : v["buttons_effects"]) {
				if (!k.is_object())
					throw InvalidDialogFileException(i, "buttons_effects field contains a non object element");
				if (!k.contains("gold") || !k["gold"].is_number_integer())
					throw InvalidDialogFileException(i, "gold field is not an integer");
				if (!k.contains("food") || !k["food"].is_number_integer())
					throw InvalidDialogFileException(i, "gold field is not an integer");
				if (!k.contains("army") || !k["army"].is_number_integer())
					throw InvalidDialogFileException(i, "gold field is not an integer");
				if (!k.contains("set_flags") || !k["set_flags"].is_array())
					throw InvalidDialogFileException(i, "set_flags field is not an array");
				for (size_t j = 0; j < k["set_flags"].size(); j++)
					if (!k["set_flags"][j].is_string())
						throw InvalidDialogFileException(
							i, "In effect #"+ std::to_string(j) +
							": set_flags field contains a non string element"
						);
				if (!k.contains("unset_flags") || !k["unset_flags"].is_array())
					throw InvalidDialogFileException(i, "unset_flags field is not an array");
				for (size_t j = 0; j < k["unset_flags"].size(); j++)
					if (!k["unset_flags"][j].is_string())
						throw InvalidDialogFileException(
							i, "In effect #"+ std::to_string(j) +
							   ": unset_flags field contains a non string element"
						);
			}
		}
#endif

		for (const auto &v : val)
			this->_dialogs[name].emplace_back(v, resources.textures);
		stream.close();
	}

	void QuestMgr::update(Resources &)
	{
	}

	void QuestMgr::showDialog(const std::string &file, unsigned int id, tgui::Gui &gui)
	{
		unsigned y = 0;
		auto &val = this->_dialogs.at(file).at(id);
		int size = val.buttons.size();
		double ysize = (60 - (size - 1) / 3 * 10) / ((size - 1) / 3 + 1.);
		auto title = this->_panel->get<tgui::Label>("Title");
		auto desc = this->_panel->get<tgui::TextBox>("TextBox1");
		auto fct = [this, &val, id, file, &gui](unsigned butId) {
			if (this->_onClickButton)
				this->_onClickButton({val, butId, file, id});
			gui.remove(this->_panel);
		};

		this->_selected = {file, id};
		title->setText(val.title);
		desc->setText(val.description);
		desc->setVerticalScrollbarValue(0);
		this->_panel->add(val.pic);
		for (int left = size, index = 0; left > 0; left -= 3, y++) {
			auto start = left > 3 ? 3 : left;
			auto xsize = (500 - (start - 1) * 10.) / start;

			for (int i = start; i; i--) {
				auto but = tgui::Button::create(val.buttons[index]);
				auto *renderer = but->getRenderer();

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
		gui.add(this->_panel);
	}

	void QuestMgr::onClick(const std::function<void(const ClickEvent &event)> &handler)
	{
		this->_onClickButton = handler;
	}

	QuestMgr::Quest::Quest(const nlohmann::json &json, std::map<std::string, sf::Texture> &textures) :
		pic(tgui::Picture::create(textures[json["picture"]])),
		title(json["title"]),
		description(json["description"]),
		buttons(json["buttons"]),
		requirements(json["requirements"]),
		weekRange(json["week_no"], json["expire_time"]),
		buttons_effects(json["buttons_effects"].begin(), json["buttons_effects"].end())
	{
		this->weekRange.second += this->weekRange.first;
		this->pic->setSize(150, 150);
		this->pic->setPosition(390, 50);
	}

	QuestMgr::Effect::Effect(const nlohmann::json &json) :
		setFlags(json["set_flags"]),
		unsetFlags(json["unset_flags"]),
		goldChange(json["gold"]),
		foodChange(json["food"]),
		armyChange(json["army"])
	{
	}
}