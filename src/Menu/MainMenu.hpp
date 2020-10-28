//
// Created by timcav on 27/10/2020.
//

#ifndef UBC_MAINMENU_H
#define UBC_MAINMENU_H


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"
#include "../DialogMgr.hpp"

namespace UntilBeingCrowned
{
    class MainMenu : public Menu {
    private:
        Resources &_res;
        tgui::Gui &_gui;
        MenuMgr &_mgr;
        DialogMgr &_dialogs;

    public:
        MainMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, DialogMgr &dialogs);
        void switched(bool isActive) override;
        void render() override;
        void handleEvent(const Input::Event &event) override;

        void newGameButtonHandler(tgui::Widget::Ptr widget, const std::string& signalName);
        void loadGameButtonHandler(tgui::Widget::Ptr widget, const std::string& signalName);
        void optionsButtonHandler(tgui::Widget::Ptr widget, const std::string& signalName);
        static void exitButtonHandler(tgui::Widget::Ptr widget, const std::string& signalName);

    };
}



#endif //UBC_MAINMENU_H
