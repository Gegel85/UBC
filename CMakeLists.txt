cmake_minimum_required(VERSION 3.10)
project(UBC)

set(CMAKE_CXX_STANDARD 17)

include_directories(nlohmann)

if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if (CMAKE_COMPILER_IS_GNUCC)
		add_compile_options(-Wall -Wextra -W -g -D_DEBUG)
	endif (CMAKE_COMPILER_IS_GNUCC)
endif ()
if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
	if (CMAKE_COMPILER_IS_GNUCC)
		if (WIN32)
			add_link_options(-mwindows)
		endif (WIN32)
	endif (CMAKE_COMPILER_IS_GNUCC)
endif ()
if (WIN32)
	set(ICON icon.rc)
endif (WIN32)

include_directories(nlohmann)

set(
	UBC_SRC
	src/Utils.cpp
	src/Utils.hpp
	src/main.cpp
	src/Logger.cpp
	src/Logger.hpp
	src/Exceptions.cpp
	src/Exceptions.hpp
	src/Menu/Exceptions.hpp
	src/Menu/Menu.cpp
	src/Menu/Menu.hpp
	src/Menu/MenuMgr.cpp
	src/Menu/MenuMgr.hpp
	src/Input/Input.cpp
	src/Input/Input.hpp
	src/Input/SFMLJoypad.cpp
	src/Input/SFMLJoypad.hpp
	src/Input/SFMLKeyboard.cpp
	src/Input/SFMLKeyboard.hpp
	src/Rendering/Screen.cpp
	src/Rendering/Screen.hpp
	src/Resources/Logger.hpp
	src/DataType/Rect.hpp
	src/DataType/Vector.hpp
	src/Resources/Logger.cpp
	src/Resources/version.hpp
	src/Resources/Game.hpp
	src/Resources/State.hpp
	src/Resources/Resources.cpp
	src/Resources/Resources.hpp
	src/Loader.cpp
	src/Logger.hpp
	src/Resources/Settings.hpp
	src/Menu/InGameMenu.cpp
	src/Menu/InGameMenu.hpp
	#src/DialogMgr.cpp
	#src/DialogMgr.hpp
	src/Menu/MainMenu.cpp
	src/Menu/MainMenu.hpp
	src/QuestMgr.cpp
	src/QuestMgr.hpp
	src/Resources/GameState.hpp)

if (WIN32)
	add_executable(UBC ${UBC_SRC} icon.rc)
	target_link_libraries(
		UBC
		sfml-window
		sfml-system
		sfml-graphics
		sfml-audio
		tgui
	)
else (WIN32)
	add_executable(UBC ${UBC_SRC})
	target_link_libraries(
		UBC
		sfml-window
		sfml-system
		sfml-graphics
		sfml-audio
		tgui
	)
endif (WIN32)
