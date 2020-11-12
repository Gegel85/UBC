//
// Created by timcav on 28/10/2020.
//

#include "OptionMenu.hpp"
#include "../DataType/Vector.hpp"
#include "../Rendering//Screen.hpp"
#include <iostream>

namespace UntilBeingCrowned
{
	OptionMenu::OptionMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res) :
		_res(res),
		_gui(gui),
		_mgr(mgr),
		_initMusicVolume(100),
		_newMusicVolume(100),
		_initSoundVolume(100),
		_newSoundVolume(100),
		_initFullscreen(false),
		_newFullScreen(false) {
	}

	void OptionMenu::switched(bool isActive) {
		if (!isActive) {
			this->_gui.removeAllWidgets();
			return;
		}

		this->_gui.loadWidgetsFromFile("gui/optionMenu.gui");

		auto checkBox = this->_gui.get<tgui::CheckBox>("fullscreenCheckBox");

		this->_gui.get<tgui::Button>("back")->connect(tgui::Signals::Button::Pressed, &OptionMenu::back, this);
		this->_gui.get<tgui::Button>("save")->connect(tgui::Signals::Button::Pressed, &OptionMenu::save, this);
		this->_sliderMusic = this->_gui.get<tgui::Slider>("volumeMusicSlider");
		this->_sliderMusic->connect(tgui::Signals::Slider::ValueChanged, &OptionMenu::setMusicVolume, this);
		this->_sliderSfx = this->_gui.get<tgui::Slider>("volumeSoundSlider");
		this->_sliderSfx->connect(tgui::Signals::Slider::ValueChanged, &OptionMenu::setSoundVolume, this);
		this->_initMusicVolume = this->_res.getMusicVolume();
		this->_newMusicVolume = this->_initMusicVolume;
		this->_sliderMusic->setValue(this->_initMusicVolume);
		this->_initSoundVolume = this->_res.getSoundVolume();
		this->_newSoundVolume = this->_initSoundVolume;
		this->_sliderSfx->setValue(this->_initSoundVolume);

		checkBox->setChecked(this->_initFullscreen);
		checkBox->connect(tgui::Signals::RadioButton::Checked,    &OptionMenu::setFullscreen, this, true);
		checkBox->connect(tgui::Signals::RadioButton::Unchecked,  &OptionMenu::setFullscreen, this, false);
		this->_initFullscreen = this->_res.screen.isFullscreen();
		this->_newFullScreen = this->_initFullscreen;
	}

	void OptionMenu::render() {

	}

	void OptionMenu::handleEvent(const Input::Event &) {

	}

	void OptionMenu::back() {
		this->_res.setMusicVolume(this->_initMusicVolume);
		this->_res.setSoundVolume(this->_initSoundVolume);
		if (this->_initFullscreen != this->_newFullScreen)
			this->setFullscreen(this->_initFullscreen);
		this->_mgr.changeMenu("main");
	}

	void OptionMenu::setMusicVolume() {
		this->_newMusicVolume = this->_sliderMusic->getValue();
		this->_res.setMusicVolume(_newMusicVolume);
	}

	void OptionMenu::setSoundVolume() {
		this->_newSoundVolume = this->_sliderSfx->getValue();
		this->_res.setSoundVolume(_newSoundVolume);
	}

	void OptionMenu::setFullscreen(bool b) {
		this->_newFullScreen = b;
		this->_res.screen.reOpen(
			this->_res.screen.getTitle(),
			1360,
			768,
			b
		);
	}

	void OptionMenu::save() {
		this->_initMusicVolume = this->_newMusicVolume;
		this->_initSoundVolume = this->_newSoundVolume;
		this->_initFullscreen = this->_newFullScreen;
	}
}
