//
// Created by timcav on 28/10/2020.
//

#include "OptionMenu.hpp"


namespace UntilBeingCrowned {
    OptionMenu::OptionMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs) :
            _res(res),
            _gui(gui),
            _mgr(mgr),
            _dialogs(dialogs)
    {
    }

    void OptionMenu::switched(bool isActive)
    {
        if (!isActive) {
            this->_gui.removeAllWidgets();
            return;
        }

        this->_gui.loadWidgetsFromFile("gui/optionMenu.gui");
        this->_gui.get("back")->cast<tgui::Button>()->connect(tgui::Signals::Button::Pressed, OptionMenu::backButtonHandler, std::ref(*this));

    }

    void OptionMenu::render()
    {

    }

    void OptionMenu::handleEvent(const Input::Event &)
    {

    }

    void OptionMenu::backButton() {
        this->_mgr.changeMenu("main");
    }

    void OptionMenu::backButtonHandler(OptionMenu &m) {
        m.backButton();
    }


}

