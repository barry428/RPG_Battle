#include "Menu.h"

class Map;

Menu::Menu(GameWindow *lw, GameWindow *aw, GameWindow *ew, GameWindow *cw)
        : logWin(lw), alliesWin(aw), enemiesWin(ew), commandWin(cw) {

    Table table;
    table.add_row({"1. 继续游戏"});
    table.add_row({"2. 新的开始"});
    const auto& rows = table.getFormattedRows();
    for (const auto& row : rows) {
        logWin->printLogCenter(logEntries, row);
    }

    commandWin->displayCommand("你的选择是：");

    while (true) {
        char input = wgetch(commandWin->win);
        int choice = input - '0';

        if (choice == 1) {
            Map map(logWin, alliesWin, enemiesWin, commandWin);
            map.runMap();
            break;
        } else if (choice == 2) {
            logEntries.clear();
            logEntries.push_back("故事开端：");
            logEntries.push_back("在未来的某个时代，地球已经极度发展，科技达到了前所未有的高度。");
            logEntries.push_back("然而，随着资源的枯竭和环境的恶化，人类开始寻求新的生存之道。");
            logEntries.push_back("在这个背景下，中央城市的一位年轻科学家（玩家角色）发现了一系列古老的");
            logEntries.push_back("符号和地图，这些符号指引着通向隐藏在世界各地的秘密技术和未知力量的路径。");
            logWin->printLog(logEntries, "", 30);
            commandWin->displayCommand("请选择：1. 开始游戏 2. 重看游戏介绍");
        }
    }
}
