cmake_minimum_required(VERSION 3.25)
project(ncurses)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "arm64")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(ncurses main.cpp battle.cpp GameWindow.cpp Character.cpp Skill.cpp GameInitialization.cpp CharacterFactory.h SkillsManager.cpp Map.cpp Map.cpp MapGenerator.cpp)
target_link_libraries(ncurses ${CURSES_LIBRARIES})

