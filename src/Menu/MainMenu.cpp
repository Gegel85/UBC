//
// Created by timcav on 27/10/2020.
//

#include "MainMenu.hpp"

namespace UntilBeingCrowned {
    MainMenu::MainMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs) :
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
        this->_gui.get("newGame")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, MainMenu::newGameButtonHandler, std::ref(*this));
        this->_gui.get("loadGame")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, MainMenu::loadGameButtonHandler, std::ref(*this));
        this->_gui.get("options")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, MainMenu::optionsButtonHandler, std::ref(*this));
        this->_gui.get("exit")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, MainMenu::exitButtonHandler, std::ref(*this));

    }

    void MainMenu::render()
    {

    }

    void MainMenu::handleEvent(const Input::Event &)
    {

    }

    void MainMenu::newGameButton() {
        this->_mgr.changeMenu("new_game");
    }

    void MainMenu::newGameButtonHandler(MainMenu &m) {
        m.newGameButton();
    }

    void MainMenu::loadGameButton() {
        this->_mgr.changeMenu("load");
    }

    void MainMenu::loadGameButtonHandler(MainMenu &m) {
        m.loadGameButton();
    }

    void MainMenu::optionsButton() {
        this->_mgr.changeMenu("option");
    }

    void MainMenu::optionsButtonHandler(MainMenu &m) {
        m.optionsButton();
    }
    void MainMenu::exitButton() {
        this->_res.screen.close();
    }

    void MainMenu::exitButtonHandler(MainMenu &m) {
        m.exitButton();
    }
}

