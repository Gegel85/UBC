//
// Created by andgel on 13/10/2020.
//

#ifndef UBC_RESOURCES_HPP
#define UBC_RESOURCES_HPP


#include <array>
#include <random>
#include <SFML/Audio.hpp>
#include "version.hpp"
#include "Logger.hpp"
#include "../Rendering/Screen.hpp"

#define MAX_PLAYING_SFX 64

namespace UntilBeingCrowned
{
	struct Resources {
	private:
		//! @brief The ID of the last played sound
		mutable unsigned _lastPlayedSound = 0;

	public:
		//! @brief The main window
		Rendering::Screen screen{
			"Until Being Crowned " UBC_VERSION_STRING, 1360, 768
		};

		//! @brief The icon of the screen
		sf::Image icon;

		//! @brief A random generator
		std::mt19937 random;

		//! @brief The loaded musics
		std::map<std::string, std::pair<sf::Music, std::string>> musics;

		//! @brief The loaded sprites
		std::map<std::string, sf::Texture> textures;

		//! @brief The loaded sfx
		std::map<std::string, sf::SoundBuffer> soundBuffers;

		//! @brief The sound objects used to play sfx
		mutable std::array<sf::Sound, MAX_PLAYING_SFX> sounds;

		//! @brief The global font
		sf::Font font;

		//! @brief The end messages
		std::map<std::string, std::string> endMessages;

		//! @brief Plays a sound effect
		//! @param id The id of the sound effect to play
		//! @return The sound index assigned to this sfx
		unsigned char playSound(const std::string &id);

		//! @brief Plays a music
		//! @param id The id of the music to play
		void playMusic(const std::string &id);

		//! @brief Stops any music currently playing
		void stopMusic();

		//! @brief Changes the volume of all the musics.
		//! @param newVolume New volume.
		void setMusicVolume(float newVolume);

		//! @brief get the volume of all the musics.
		float getMusicVolume() const;

		//! @brief Changes the volume of all the sounds.
		//! @param newVolume New volume.
		void setSoundVolume(float newVolume);

		//! @brief get the volume of all the sounds.
		float getSoundVolume() const;
	};
}


#endif //UBC_RESOURCES_HPP
