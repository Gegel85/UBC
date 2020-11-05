//
// Created by timcav on 28/10/2020.
//

#include "OptionMenu.hpp"
#include "../DataType/Vector.hpp"
#include "../Rendering//Screen.hpp"
#include <iostream>

namespace UntilBeingCrowned {
    OptionMenu::OptionMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs) :
            _res(res),
            _gui(gui),
            _mgr(mgr),
            _dialogs(dialogs),
            _initMusicVolume(100),
            _newMusicVolume(100),
            _initSoundVolume(100),
            _newSoundVolume(100),
            _initFullscreen(false),
            _newFullScreen(false)
    {
    }

    void OptionMenu::switched(bool isActive)
    {
        if (!isActive) {
            this->_gui.removeAllWidgets();
            return;
        }

        this->_gui.loadWidgetsFromFile("gui/optionMenu.gui");
        this->_gui.get<tgui::Button>("back")->connect(tgui::Signals::Button::Pressed, OptionMenu::backButtonHandler, std::ref(*this));
        this->_gui.get<tgui::Button>("save")->connect(tgui::Signals::Button::Pressed, OptionMenu::saveButtonHandler, std::ref(*this));

        _sM =  this->_gui.get<tgui::Slider>("volumeMusicSlider");
		_sM->connect(tgui::Signals::Slider::ValueChanged, OptionMenu::musicVolumSlider,std::ref(*this), std::ref(_sM));
		_sS = this->_gui.get<tgui::Slider>("volumeSoundSlider");
		_sS->connect(tgui::Signals::Slider::ValueChanged, OptionMenu::soundVolumSlider,std::ref(*this), std::ref(_sS));
		_initMusicVolume = this->_res.getMusicVolume();
		_newMusicVolume = _initMusicVolume;
		_sM->setValue(_initMusicVolume);
		_initSoundVolume = this->_res.getSoundVolume();
		_newSoundVolume = _initSoundVolume;
		_sS->setValue(_initSoundVolume);

		this->_gui.get<tgui::CheckBox>("fullscreenCheckBox")->setChecked(_initFullscreen);
		this->_gui.get<tgui::CheckBox>("fullscreenCheckBox")->connect(tgui::Signals::RadioButton::Checked, OptionMenu::fullScreenChecked, std::ref(*this));
		this->_gui.get<tgui::CheckBox>("fullscreenCheckBox")->connect(tgui::Signals::RadioButton::Unchecked, OptionMenu::fullScreenUnchecked, std::ref(*this));
		_initFullscreen = this->_res.screen.isFullscreen();
		_newFullScreen = _initFullscreen;
    }

    void OptionMenu::render()
    {

    }

    void OptionMenu::handleEvent(const Input::Event &)
    {

    }

    void OptionMenu::back() {
		this->_res.setMusicVolume( _initMusicVolume);
		this->_res.setSoundVolume( _initSoundVolume);
		if (_initFullscreen != _newFullScreen) this->setFullscreen(_initFullscreen);
        this->_mgr.changeMenu("main");
    }

    void OptionMenu::backButtonHandler(OptionMenu &m) {
        m.back();
    }

	void OptionMenu::setMusicVolume(float i) {
		_newMusicVolume = i;
		this->_res.setMusicVolume( _newMusicVolume);
    }

	void OptionMenu::musicVolumSlider(OptionMenu &m, const std::shared_ptr<tgui::Slider>& s) {
		if (s) {
			m.setMusicVolume(s->getValue());
		}
	}

	void OptionMenu::setSoundVolume(float i) {
		_newSoundVolume = i;
		this->_res.setSoundVolume( _newSoundVolume);
	}

	void OptionMenu::soundVolumSlider(OptionMenu &m, const std::shared_ptr<tgui::Slider>& s) {
    	if (s) {
			m.setSoundVolume(s->getValue());
		}
	}

	void OptionMenu::setFullscreen(bool b) {
		_newFullScreen = b;
		this->_res.screen.reOpen(
			this->_res.screen.getTitle(),
			1360,
			768,
			b
		);

	}

	void OptionMenu::fullScreenChecked(OptionMenu &m) {
    	m.setFullscreen(true);
	}

	void OptionMenu::fullScreenUnchecked(OptionMenu &m) {
		m.setFullscreen(false);
	}


	void OptionMenu::save() {
		_initMusicVolume = _newMusicVolume;
		_initSoundVolume = _newSoundVolume;
		_initFullscreen = _newFullScreen;
	}

    void OptionMenu::saveButtonHandler(OptionMenu &m) {
        m.save();
    }


}

