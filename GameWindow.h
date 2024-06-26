#pragma once

#include <ncurses.h>
#include <deque>
#include <string>
#include <vector>
#include <locale.h>
#include <thread>
#include "Table.cpp"

class GameWindow {
public:
    WINDOW* win;
    int height, width, start_y, start_x;

    GameWindow(int h, int w, int sy, int sx);
    ~GameWindow();
    void printLog(std::deque<std::string>& log, const std::string& message);
    void printLog(std::deque<std::string>& log, const std::string& message, const int sleepTime);
    void printLogCenter(std::deque<std::string>& log, const std::string& message);
    void updateStatus(const std::vector<std::string>& statuses);
    void displayCommand(const std::string& command);
    void clearWindow();
    void refreshWindow();
};
