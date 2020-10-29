//
// Created by timcav on 28/10/2020.
//

#include "LoadMenu.hpp"


namespace UntilBeingCrowned {
    LoadMenu::LoadMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs) :
            _res(res),
            _gui(gui),
            _mgr(mgr),
            _dialogs(dialogs)
    {
    }

    void LoadMenu::switched(bool isActive)
    {
        if (!isActive) {
            this->_gui.removeAllWidgets();
            return;
        }

        this->_gui.loadWidgetsFromFile("gui/loadMenu.gui");
        this->_gui.get("back")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, LoadMenu::backButtonHandler, std::ref(*this));
    }

    void LoadMenu::render()
    {

    }

    void LoadMenu::handleEvent(const Input::Event &)
    {

    }

    void LoadMenu::backButton() {
        this->_mgr.changeMenu("main");
    }

    void LoadMenu::backButtonHandler(LoadMenu &m) {
        m.backButton();
    }


}

