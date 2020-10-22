//
// Created by Gegel85 on 24/09/2019.
//

#include <filesystem>
#include "Loader.hpp"
#include "Exceptions.hpp"
#include "Input/SFMLKeyboard.hpp"
#include "Input/SFMLJoypad.hpp"
#include "Utils.hpp"

namespace UntilBeingCrowned
{
	bool Loader::loadFile(Settings &, sf::SoundBuffer &buffer, nlohmann::json &path)
	{
		return buffer.loadFromFile("assets/" + path.get<std::string>());
	}

	bool Loader::loadFile(Settings &settings, std::pair<sf::Music, std::string> &music, nlohmann::json &obj)
	{
		bool result = music.first.openFromFile("assets/" + obj["path"].get<std::string>());

		music.second = obj["description"].is_null() ? "" : obj["description"];
		music.first.setLoop(true);
		if (!obj["loop_points"].is_null())
			music.first.setLoopPoints(sf::Music::TimeSpan{
				sf::milliseconds(obj["loop_points"]["offset"]),
				sf::milliseconds(obj["loop_points"]["length"])
			});

		music.first.setVolume(settings.musicVolume);
		return result;
	}

	bool Loader::loadFile(Settings &, sf::Texture &texture, nlohmann::json &path)
	{
		return texture.loadFromFile("assets/" + path.get<std::string>());
	}

	void Loader::saveSettings(Settings &settings)
	{
		std::filesystem::create_directories("saves");

		std::ofstream stream("saves/settings.sav");

		settings.input->serialize(stream);
		stream << std::endl << settings.musicVolume << std::endl << settings.sfxVolume;
		stream.close();
	}

	void Loader::loadSettings(Game &game)
	{
		std::ifstream stream("saves/settings.sav");

		logger.info("Loading settings");
		game.state.settings.input.reset(new Inputs::SFMLKeyboard(&game.resources.screen));
		if (stream.fail()) {
			logger.error("Cannot open file save/settings.sav " + std::string(strerror(errno)));
			game.state.settings.musicVolume = 100;
			game.state.settings.sfxVolume = 100;
		} else {
			game.state.settings.input->unserialize(stream);
			stream >> game.state.settings.musicVolume >> game.state.settings.sfxVolume;
		}
		game.resources.setMusicVolume(game.state.settings.musicVolume);
		game.resources.setSoundVolume(game.state.settings.sfxVolume);
	}

	void Loader::loadAssets(Game &game)
	{
		std::ifstream stream{"assets/list.json"};
		nlohmann::json data;

		loadSettings(game);

		//We do this because on MinGW std::random_device always produce the same output
		//(also we don't need the most unpredictable seed)
		game.resources.random.seed(time(nullptr));

		logger.debug("Opening file assets/list.json");
		if (stream.fail())
			throw CorruptedAssetsListException("Cannot open assets list from assets/list.json");

		try {
			logger.debug("Parsing json");
			stream >> data;
			stream.close();

			logger.debug("Loading icon");
			if (data["icon"].is_null())
				logger.warn("No Icon is marked for loading");
			else if (!game.resources.icon.loadFromFile("assets/" + data["icon"].get<std::string>()))
				logger.error("Cannot load file assets/" + data["icon"].get<std::string>());
			else
				game.resources.screen.setIcon(
					game.resources.icon.getSize().x,
					game.resources.icon.getSize().y,
					game.resources.icon.getPixelsPtr()
				);

			logger.debug("Loading musics");
			loadAssetsFromJson(game.state.settings, "Musics", data["musics"], game.resources.musics);

			logger.debug("Loading sfx");
			loadAssetsFromJson(game.state.settings, "Sound effects", data["sfx"], game.resources.soundBuffers);

			logger.debug("Loading sprites");
			loadAssetsFromJson(game.state.settings, "Sprites", data["sprites"], game.resources.textures);
		} catch (nlohmann::detail::parse_error &e) {
			throw CorruptedAssetsListException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw CorruptedAssetsListException("The JSON values are invalid: " + std::string(e.what()));
		}

		logger.debug("Loading dialog");
		game.state.dialogs.loadFile("assets/dialogs.json", game.resources);
	}
}