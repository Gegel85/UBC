//
// Created by timcav on 27/10/2020.
//

#include "MainMenu.hpp"
#include <iostream>

namespace UntilBeingCrowned {
    MainMenu::MainMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, DialogMgr &dialogs) :
            _res(res),
            _gui(gui),
            _mgr(mgr),
            _dialogs(dialogs)
    {
    }

    void MainMenu::switched(bool isActive)
    {
        if (!isActive) {
            this->_gui.removeAllWidgets();
            return;
        }

        this->_gui.loadWidgetsFromFile("gui/mainMenu.gui");
        this->_gui.get("newGame")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, newGameButtonHandler);
        this->_gui.get("loadGame")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, MainMenu::loadGameButtonHandler);
        this->_gui.get("options")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, MainMenu::optionsButtonHandler);
        this->_gui.get("exit")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, MainMenu::exitButtonHandler);

    }

    void MainMenu::render()
    {

    }

    void MainMenu::handleEvent(const Input::Event &)
    {

    }

    void MainMenu::newGameButtonHandler(tgui::Widget::Ptr widget, const std::string &signalName) {

    }

    void MainMenu::loadGameButtonHandler(tgui::Widget::Ptr widget, const std::string &signalName) {
        std::cout << "load" << std::endl;
    }

    void MainMenu::optionsButtonHandler(tgui::Widget::Ptr widget, const std::string &signalName) {
        std::cout << "option" << std::endl;
    }

    void MainMenu::exitButtonHandler(tgui::Widget::Ptr widget, const std::string &signalName) {
        std::cout << "exit" << std::endl;
    }
}

