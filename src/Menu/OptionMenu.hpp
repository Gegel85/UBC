//
// Created by timcav on 28/10/2020.
//

#ifndef UBC_OPTIONMENU_HPP
#define UBC_OPTIONMENU_HPP


#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources/Resources.hpp"
#include "../QuestMgr.hpp"

namespace UntilBeingCrowned
{
	class OptionMenu : public Menu {
	private:
		Resources &_res;
		tgui::Gui &_gui;
		MenuMgr &_mgr;
		Game &_game;

		float _initMusicVolume;
		float _newMusicVolume;
		float _initSoundVolume;
		float _newSoundVolume;
		bool _initFullscreen;
		bool _newFullScreen;

		std::shared_ptr<tgui::Slider> _sliderMusic;
		std::shared_ptr<tgui::Slider> _sliderSfx;

		void back();
		void setMusicVolume();
		void setSoundVolume();
		void setFullscreen(bool);
		void save();

	public:
		OptionMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, Game &_game);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;
	};
}



#endif //UBC_OPTIONMENU_HPP
