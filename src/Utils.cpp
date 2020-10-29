//
// Created by Gegel85 on 26/10/2019.
//


#include <algorithm>
#include <filesystem>
#include <iostream>
#include <sstream>
#ifndef _WIN32
#include <vector>
#include <TGUI/TGUI.hpp>

#define mkdir(path) mkdir(path, 0755)
#define ICON_ERROR_PATH "assets/error.png"
#else
#include <io.h>
#endif

#include "Utils.hpp"
#include "Exceptions.hpp"
#include "Resources/Logger.hpp"

namespace UntilBeingCrowned::Utils
{
	int	dispMsg(const std::string &title, const std::string &content, int variate)
	{
#ifdef _WIN32
		return (MessageBox(nullptr, content.c_str(), title.c_str(), variate));
#else
		auto button = tgui::Button::create("OK");
		auto text = tgui::TextBox::create();
		tgui::Gui gui;
		auto font = tgui::getGlobalFont();
		const auto startWidth = button->getSize().x + 102;
		unsigned width = startWidth;
		unsigned height = button->getSize().y + 60;
		float currentWidth = startWidth;
		auto size = text->getTextSize();

		std::cerr << title << std::endl << content << std::endl;
		for (char c : content) {
			currentWidth += font.getGlyph(c, size, false).advance;
			width = std::max(static_cast<unsigned>(currentWidth), width);
			if (c == '\n' || c == '\r')
				currentWidth = startWidth;
			if (c == '\n' || c == '\v')
				height += size;
			if (currentWidth >= 700) {
				currentWidth = startWidth;
				height += size;
			}
		}

		sf::RenderWindow win{{std::min(700U, width), std::min(220U, height)}, title, sf::Style::Titlebar | sf::Style::Close};
		sf::Event event;

		try {
			auto pic = tgui::Picture::create(ICON_ERROR_PATH);

			if (variate & MB_ICONERROR)
				gui.add(pic);
			pic->setPosition(10, 10);
			pic->setSize(32, 32);
		} catch (tgui::Exception &) {}
		gui.setTarget(win);
		gui.add(button, "ok");
		gui.add(text);

		button->setPosition("&.w - w - 10", "&.h - h - 10");
		button->connect("Pressed", [&win]{
			win.close();
		});

		text->setText(content);
		text->setPosition(52, 10);
		text->setSize("ok.x - 62", "ok.y - 20");
		text->setReadOnly();
		text->getRenderer()->setBorderColor("transparent");
		text->getRenderer()->setBackgroundColor("transparent");

		while (win.isOpen()) {
			while (win.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					win.close();
				gui.handleEvent(event);
			}

			win.clear({230, 230, 230, 255});
			gui.draw();
			win.display();
		}

		return 0;
#endif
	}

	std::string floatToString(float nb)
	{
		std::stringstream stream;

		stream << nb;
		return stream.str();
	}

	/*double min(double v)
	{
		return v;
	}

	double min(double v1, double args...)
	{
		return std::fmin(v1, min(args));
	}

	double max(double v)
	{
		return v;
	}

	double max(double v1, double args...)
	{
		return std::fmax(v1, max(args));
	}*/

	void rename(const std::string &oldName, const std::string &newName)
	{
		if (!std::filesystem::exists(oldName))
			throw FileNotFoundException(std::move(oldName));
		if (std::filesystem::exists(newName))
			std::filesystem::remove(newName);
		std::filesystem::rename(oldName, newName);
	}
}
