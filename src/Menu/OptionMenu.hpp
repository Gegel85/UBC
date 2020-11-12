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
		QuestMgr &_dialogs;
		Game &_game;

		float _initMusicVolume;
		float _newMusicVolume;
		float _initSoundVolume;
		float _newSoundVolume;
		bool _initFullscreen;
		bool _newFullScreen;

		std::shared_ptr<tgui::Slider> _sM;
		std::shared_ptr<tgui::Slider> _sS;

	public:
		OptionMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs, Game &game);
		void switched(bool isActive) override;
		void render() override;
		void handleEvent(const Input::Event &event) override;

		void back();
		void setMusicVolume(float);
		void setSoundVolume(float);
		void setFullscreen(bool);
		void save();

	private:
		static void backButtonHandler(OptionMenu &);
		static void musicVolumSlider(OptionMenu &, const std::shared_ptr<tgui::Slider> &);
		static void soundVolumSlider(OptionMenu &, const std::shared_ptr<tgui::Slider> &);
		static void fullScreenChecked(OptionMenu &);
		static void fullScreenUnchecked(OptionMenu &);
		static void saveButtonHandler(OptionMenu &);

	};
}



#endif //UBC_OPTIONMENU_HPP
