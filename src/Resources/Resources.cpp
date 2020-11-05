//
// Created by andgel on 13/10/2020.
//

#include "Resources.hpp"

namespace UntilBeingCrowned
{
	unsigned char Resources::playSound(const std::string &id)
	{
		this->_lastPlayedSound = (this->_lastPlayedSound + 1) % this->sounds.size();
		try {
			this->sounds[this->_lastPlayedSound].setBuffer(this->soundBuffers.at(id));
			this->sounds[this->_lastPlayedSound].play();
		} catch (std::out_of_range &e) {
			logger.error("Cannot play sound " + id);
		}
		return this->_lastPlayedSound;
	}

	void Resources::playMusic(const std::string &id)
	{
		try {
			if (this->musics.at(id).first.getStatus() == sf::Music::Playing)
				return;
		} catch (std::out_of_range &e) {
			return logger.error("Cannot play music " + id);
		}

		this->stopMusic();
		this->musics.at(id).first.play();
	}

	void Resources::stopMusic()
	{
		for (auto &music : this->musics)
			music.second.first.stop();
	}

	void Resources::setMusicVolume(float newVolume)
	{
		for (auto &music : this->musics)
			music.second.first.setVolume(newVolume);
	}

	float Resources::getMusicVolume() const{
		return this->musics.begin()->second.first.getVolume();
	}

	void Resources::setSoundVolume(float newVolume)
	{
		for (auto &sound : this->sounds)
			sound.setVolume(newVolume);
	}

	float Resources::getSoundVolume() const {
		return this->sounds.begin()->getVolume();
	}
}