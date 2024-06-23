#pragma once

#include "GameWindow.h"
#include "Map.h"
#include "Table.cpp"
#include <vector>
#include <deque>
#include <string>
#include <random>

class Menu {
public:

    GameWindow *logWin;
    GameWindow *alliesWin;
    GameWindow *enemiesWin;
    GameWindow *commandWin;
    std::deque<std::string> logEntries;

    Menu(GameWindow *lw, GameWindow *aw, GameWindow *ew, GameWindow *cw);

};
