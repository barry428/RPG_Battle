// main.cpp
#include "Map.h"
#include "Menu.h"
#include "Battle.h"
#include "GameInitialization.h"

int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();

    // 获取屏幕尺寸
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    max_y = max_y > 40 ? 40 : max_y;
    max_x = max_x > 120 ? 120 : max_x;

    // 计算窗口尺寸
    int bottom_height = 4;  // 底部命令窗口的高度
    int top_height = 8;  // 上部窗口的高度
    int middle_height = max_y / 2;  // 中间日志窗口的高度
    int half_width = max_x / 2;  // 上部窗口的一半宽度

    GameInitialization::initializeCharacters();

    GameWindow alliesWin(top_height, half_width, 0, 0);
    GameWindow enemiesWin(top_height, half_width, 0, half_width);
    GameWindow logWin(middle_height, max_x, top_height, 0);
    GameWindow commandWin(bottom_height, max_x, top_height + middle_height, 0);

    Menu menu(&logWin, &alliesWin, &enemiesWin, &commandWin);

//    Map map(&logWin, &alliesWin, &enemiesWin, &commandWin);
//    map.runMap();
//    Battle battle(&logWin, &alliesWin, &enemiesWin, &commandWin);
//    battle.runBattle();
//
//    endwin();
    return 0;
}
