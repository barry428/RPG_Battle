// Battle.h
#ifndef Map_H
#define Map_H

#include "GameWindow.h"
#include "Character.h"
#include "MapGenerator.h"
#include "GameInitialization.h"
#include "Battle.h"
#include <vector>
#include <deque>

class MapGenerator;
class Battle;

class Map {
public:
    GameWindow *logWin;
    GameWindow *alliesWin;
    GameWindow *enemiesWin;
    GameWindow *commandWin;
    std::vector<Character *> allies;
    std::deque<std::string> logEntries;
    static std::string loc;
    static int index;
    static int mainMapIndex;
    static int subMapIndex;
    static int npcIndex ;

    Map(GameWindow *lw, GameWindow *aw, GameWindow *ew, GameWindow *cw);
    void initializeCharacters();
    std::vector<std::string> alliesInfo();
    void runMap();

    void mainMap();

    void subMap(int mainMapId);

    void showNpc(int subMapId);

    void showAction(int npcId);

    void talk(int npcId);

    void attack(int npcId);


};

#endif