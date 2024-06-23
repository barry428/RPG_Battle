// GameWindow.cpp
#include "GameWindow.h"

GameWindow::GameWindow(int h, int w, int sy, int sx) : height(h), width(w), start_y(sy), start_x(sx) {
    win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
}

GameWindow::~GameWindow() {
    delwin(win);
}

void GameWindow::printLog(std::deque<std::string> &log, const std::string &message) {
    if (log.size() >= (height - 2)) {
        log.pop_front();
    }
    log.push_back(message);
    clearWindow();
    int line = 1;
    for (const auto &entry: log) {
        mvwprintw(win, line++, 2, "%s", entry.c_str());
    }
    refreshWindow();
}

void GameWindow::printLog(std::deque<std::string> &log, const std::string &message, const int sleepTime) {
    if (log.size() >= (height - 2)) {
        log.pop_front();
    }
    log.push_back(message);
    clearWindow();
    int line = 1;
    int col = 1;
    std::vector<wchar_t> chars;
    for (const auto &entry: log) {
        chars = Table::get_characters(entry);
        for (wchar_t wc: chars) {
            mvwprintw(win, line, col, "%lc", wc);
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            refreshWindow();
            col += Table::wchar_display_width(wc);
        }
        line++;
        col = 1;
    }
}

void GameWindow::printLogCenter(std::deque<std::string> &log, const std::string &message) {
    if (log.size() >= (height - 2)) {
        log.pop_front();
    }
    log.push_back(message);
    clearWindow();
    int line = 1;
    int start_x = 0;
    for (const auto &entry: log) {
        if (start_x == 0) {
            start_x = (this->width - entry.length()) / 2;
        }
        mvwprintw(win, line++, start_x, "%s", entry.c_str());
    }
    refreshWindow();
}

void GameWindow::updateStatus(const std::vector<std::string> &statuses) {
    clearWindow();
    int line = 1;
    for (const auto &status: statuses) {
        mvwprintw(win, line++, 2, "%s", status.c_str());
    }
    refreshWindow();
}

void GameWindow::displayCommand(const std::string &command) {
    clearWindow();
    mvwprintw(win, 1, 2, "%s", command.c_str());
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