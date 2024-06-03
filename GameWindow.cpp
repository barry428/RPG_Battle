// GameWindow.cpp
#include "GameWindow.h"

GameWindow::GameWindow(int h, int w, int sy, int sx) : height(h), width(w), start_y(sy), start_x(sx) {
    win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
}

GameWindow::~GameWindow() {
    delwin(win);
}

void GameWindow::printLog(std::deque<std::string>& log, const std::string& message) {
    if (log.size() >= (height - 2)) {
        log.pop_front();
    }
    log.push_back(message);
    clearWindow();
    int line = 1;
    for (const auto& entry : log) {
        mvwprintw(win, line++, 1, "%s", entry.c_str());
    }
    refreshWindow();
}

void GameWindow::updateStatus(const std::vector<std::string>& statuses) {
    clearWindow();
    int line = 1;
    for (const auto& status : statuses) {
        mvwprintw(win, line++, 1, "%s", status.c_str());
    }
    refreshWindow();
}

void GameWindow::displayCommand(const std::string& command) {
    clearWindow();
    mvwprintw(win, 1, 1, "%s", command.c_str());
    refreshWindow();
}

void GameWindow::clearWindow() {
    werase(win);
    box(win, 0, 0);
}

void GameWindow::refreshWindow() {
    wrefresh(win);
    box(win, 0, 0);
}