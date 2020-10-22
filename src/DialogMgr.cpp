//
// Created by andgel on 20/10/2020.
//

#include <fstream>
#include <filesystem>
#include "DialogMgr.hpp"
#include "Exceptions.hpp"

namespace UntilBeingCrowned
{
	DialogMgr::DialogMgr()
	{
		this->_panel = tgui::ScrollablePanel::create({600, 700});
		this->_panel->setPosition("&.w / 2 - w / 2", "&.h / 2 - h / 2");
		this->_panel->loadWidgetsFromFile("gui/dialog.gui");
	}

	void DialogMgr::loadFile(const std::string &path, Resources &resources)
	{
		std::ifstream stream{path};
		nlohmann::json val;
		std::string name = std::filesystem::path(path).filename().string();

		stream >> val;
		if (!val.is_array())
			throw InvalidDialogFileException("File is expected to contain an array of objects");
		if (val.empty())
			throw InvalidDialogFileException("Array is empty");
		for (const auto &v : val) {
			if (!v.is_object())
				throw InvalidDialogFileException("Element in array is not an object");
			if (!v["title"].is_string())
				throw InvalidDialogFileException("title field is not a string");
			if (!v["description"].is_string())
				throw InvalidDialogFileException("description field is not a string");
			if (!v["picture"].is_string())
				throw InvalidDialogFileException("picture field is not a string");
			if (!v["buttons"].is_array())
				throw InvalidDialogFileException("button field is not an array");
			for (const auto &k : v["buttons"])
				if (!k.is_string())
					throw InvalidDialogFileException("button field is not a string array");
			try {
				this->_pictures.at(v["picture"]);
			} catch (std::out_of_range &) {
				auto p = tgui::Picture::create(resources.textures[v["picture"]]);

				p->setSize(150, 150);
				p->setPosition(390, 50);
				this->_pictures[v["picture"]] = p;
			} catch (const std::exception &e) {
				throw InvalidDialogFileException(e.what());
			}
			this->_dialogs[name].push_back(v);
		}
		stream.close();
	}

	void DialogMgr::update(Resources &)
	{
	}

	void DialogMgr::showDialog(const std::string &file, unsigned int id, tgui::Gui &gui)
	{
		unsigned y = 0;
		auto val = this->_dialogs.at(file).at(id);
		int size = val["buttons"].size();
		double ysize = (60 - (size - 1) / 3 * 10) / ((size - 1) / 3 + 1.);
		auto title = this->_panel->get<tgui::Label>("Title");
		auto desc = this->_panel->get<tgui::TextBox>("TextBox1");
		auto fct = [this, &val, id, file, &gui](unsigned butId) {
			if (this->_onClickButton)
				this->_onClickButton(val, butId, file, id);
			gui.remove(this->_panel);
		};

		this->_selected = {file, id};
		title->setText(val["title"].get<std::string>());
		desc->setText(val["description"].get<std::string>());
		desc->setVerticalScrollbarValue(0);
		this->_panel->add(this->_pictures[val["picture"]]);
		for (int left = size, index = 0; left > 0; left -= 3, y++) {
			auto start = left > 3 ? 3 : left;
			auto xsize = (500 - (start - 1) * 10.) / start;

			for (int i = start; i; i--) {
				auto but = tgui::Button::create(val["buttons"][index].get<std::string>());
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

	void DialogMgr::onClick(const std::function<void(nlohmann::json, unsigned, const std::string &, unsigned int)> &handler)
	{
		this->_onClickButton = handler;
	}
}