//
// Created by andgel on 20/10/2020.
//

#include <fstream>
#include <filesystem>
#include "DialogMgr.hpp"
#include "Exceptions.hpp"

namespace UntilBeingCrowned
{
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
		for (auto v : val) {
			if (!v.is_object())
				throw InvalidDialogFileException("Element in array is not an object");
			if (!v["title"].is_string())
				throw InvalidDialogFileException("title field is not a string");
			if (!v["description"].is_string())
				throw InvalidDialogFileException("description field is not a string");
			if (!v["picture"].is_string())
				throw InvalidDialogFileException("picture field is not a string");
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
		gui.add(this->_makePanel(file, id), "DialogPanel");
	}

	tgui::Panel::Ptr DialogMgr::_makePanel(const std::string &file, unsigned int id)
	{
		auto panel = tgui::ScrollablePanel::create({600, 700});
		auto val = this->_dialogs.at(file).at(0);

		panel->loadWidgetsFromFile("gui/dialog.gui");

		auto title = panel->get<tgui::Label>("Title");
		auto desc = panel->get<tgui::TextBox>("TextBox1");

		title->setText(val["title"].get<std::string>());
		desc->setText(val["description"].get<std::string>());
		panel->add(this->_pictures[val["picture"]]);
		return panel;
	}
}