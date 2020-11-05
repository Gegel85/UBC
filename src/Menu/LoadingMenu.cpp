//
// Created by timcav on 28/10/2020.
//

#include "LoadingMenu.hpp"


namespace UntilBeingCrowned {
    LoadingMenu::LoadingMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs) :
            _res(res),
            _gui(gui),
            _mgr(mgr),
            _dialogs(dialogs)
    {
    }

    void LoadingMenu::switched(bool isActive)
    {
        if (!isActive) {
            this->_gui.removeAllWidgets();
            return;
        }

        this->_gui.loadWidgetsFromFile("gui/loadMenu.gui");
        this->_gui.get("back")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, LoadingMenu::backButtonHandler, std::ref(*this));
    }

    void LoadingMenu::render()
    {

    }

    void LoadingMenu::handleEvent(const Input::Event &)
    {

    }

    void LoadingMenu::backButton() {
        this->_mgr.changeMenu("main");
    }

    void LoadingMenu::backButtonHandler(LoadingMenu &m) {
        m.backButton();
    }
}

