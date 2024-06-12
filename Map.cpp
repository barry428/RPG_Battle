// Battle.cpp
#include "Map.h"
#include <string>
#include <random>

std::string Map::loc = "world";
int Map::index = 0;
int Map::mainMapIndex = 0;
int Map::subMapIndex = 0;
int Map::npcIndex = 0;

Map::Map(GameWindow *lw, GameWindow *aw, GameWindow *ew, GameWindow *cw)
        : logWin(lw), alliesWin(aw), enemiesWin(ew), commandWin(cw) {

    // 初始化玩家角色
    initializeCharacters();

    // 初始化地图数据
    MapGenerator::generateMapData();
}

void Map::initializeCharacters() {
    allies.insert(allies.end(), GameInitialization::characters.begin(), GameInitialization::characters.end());
}

/**
* 获取我方角色信息
* @return
*/
std::vector<std::string> Map::alliesInfo() {
    std::vector<std::string> status;
    for (const auto &character: GameInitialization::characters) {
        status.push_back(character->showStatus());
    }
    return status;
}

/**
 * 循环处理每一轮战斗
 */
void Map::runMap() {

    // 当前所在地图简介
    enemiesWin->updateStatus({"World"});

    // 处理主窗口
    while (true) {
        // 我方信息窗口
        alliesWin->updateStatus(alliesInfo());

        // 命令菜单
        commandWin->displayCommand("选择要去的地方: 1, 2, 3, 0.返回上级菜单");

        if (Map::loc == "mainMap") {        // 当前进入大区域了，就展示小区域
            enemiesWin->updateStatus({MapGenerator::regions[Map::mainMapIndex].name});
            subMap(Map::index);
        } else if (Map::loc == "subMap") {  // 当前在小区域了就展示npc
            enemiesWin->updateStatus({MapGenerator::regions[Map::mainMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].name});
            showNpc(Map::index);
        } else if (Map::loc == "npc") {     // 当前在npc就是展示动作
            enemiesWin->updateStatus({MapGenerator::regions[Map::mainMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs[Map::npcIndex].name});
            showAction(Map::index);
        } else if (Map::loc == "action") {
            enemiesWin->updateStatus({MapGenerator::regions[Map::mainMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs[Map::npcIndex].name});
            showAction(Map::index);
        } else if (Map::loc == "talk") {
            enemiesWin->updateStatus({MapGenerator::regions[Map::mainMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs[Map::npcIndex].name});
            Map::talk(Map::index);
        } else if (Map::loc == "attack") {
            enemiesWin->updateStatus({MapGenerator::regions[Map::mainMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].name,
                                      MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs[Map::npcIndex].name});
            Map::attack(Map::index);
        } else {
            enemiesWin->updateStatus({"World"});
            mainMap();
        }
    }
}


/**
 * 选择大区域
 */
void Map::mainMap() {
    logEntries.clear();
    logWin->printLog(logEntries, "接下来打算去哪里：");
    for (auto &[id, region]: MapGenerator::regions) {
        logWin->printLog(logEntries, "Region ID: " + std::to_string(id) + ", Name: " + region.name);
    }

    char input = wgetch(commandWin->win);
    Map::index = input - '0';
    if (Map::index > 0) {
        Map::loc = "mainMap";
        Map::mainMapIndex = Map::index;
    } else {
        Map::loc = "world";
    }

}

void Map::subMap(int mainMapId) {
    logEntries.clear();
    logWin->printLog(logEntries, "接下来打算去哪里：");
    for (auto &location: MapGenerator::regions[Map::mainMapIndex].locations) {
        logWin->printLog(logEntries, "Location ID: " + std::to_string(location.id) + ", Name: " + location.name);
    }

    char input = wgetch(commandWin->win);
    Map::index = input - '0';
    if (index > 0) {
        Map::loc = "subMap";
        Map::subMapIndex = Map::index;
    } else {
        Map::loc = "world";
    }

}

void Map::showNpc(int subMapId) {
    logEntries.clear();
    logWin->printLog(logEntries, "选择npc：");
    for (auto &npc: MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs) {
        logWin->printLog(logEntries, "NPC ID: " + std::to_string(npc.id) + ", Name: " + npc.name);
    }

    char input = wgetch(commandWin->win);
    Map::index = input - '0';
    if (index > 0) {
        Map::loc = "npc";
    } else {
        Map::loc = "mainMap";
    }
}

void Map::showAction(int npcId) {
    logEntries.clear();
    logWin->printLog(logEntries, "选择和" + MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs[Map::npcIndex].name +
                                 "：");
    logWin->printLog(logEntries, "1. 说话");
    logWin->printLog(logEntries, "2. 攻击");

    char input = wgetch(commandWin->win);
    Map::index = input - '0';
    if (index == 0) {
        Map::loc = "subMap";
    } else if (index == 1) {
        Map::loc = "talk";
    } else if (index == 2) {
        Map::loc = "attack";
    }
}

void Map::talk(int npcId) {
    logEntries.clear();
    std::string name = MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs[Map::npcIndex].name;
    logWin->printLog(logEntries, "和" + name + "聊天");

    char input = wgetch(commandWin->win);
    Map::index = input - '0';
    if (index == 0) {
        Map::loc = "action";
    } else {
        Map::loc = "talk";
    }
}

void Map::attack(int npcId) {
    logEntries.clear();
    std::string name = MapGenerator::regions[Map::mainMapIndex].locations[Map::subMapIndex].npcs[Map::npcIndex].name;
    logWin->printLog(logEntries, "和" + name + "战斗？1.开始战斗 0.返回");

    char input = wgetch(commandWin->win);
    Map::index = input - '0';
    if (index == 0) {
        Map::loc = "action";
    } else {
        // 初始化战斗
        GameInitialization::initEnemies();
        Battle battle(this->logWin, this->alliesWin, this->enemiesWin, this->commandWin);
        battle.runBattle();
        Map::loc = "action";
    }
}