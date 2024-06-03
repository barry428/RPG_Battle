// Battle.h
#ifndef BATTLE_H
#define BATTLE_H

#include "GameWindow.h"
#include "Skill.h"  // 首先包含 Skill
#include "Character.h"  // 然后包含 Character
#include <vector>
#include <deque>

class Battle {
public:
    GameWindow *logWin;
    GameWindow *alliesWin;
    GameWindow *enemiesWin;
    GameWindow *commandWin;
    std::vector<Character *> allies;
    std::vector<Character *> enemies;
    std::deque<std::string> logEntries;
    int currentTurn = 0;
    bool isAlliesTurn = true;

    Battle(GameWindow *lw, GameWindow *aw, GameWindow *ew, GameWindow *cw);

    void initializeCharacters();

    std::vector<std::string> alliesInfo();

    std::vector<std::string> enemiesInfo();

    void runBattle();

    void executeTurn();

    void nextTurn();

    int checkBattleRes();

    void handleAction(Character &actor);

    void executeEnemyAction(Character &actor);

    void printAttackTargets();

    void displayMainMenu();

    void executeMainMenu(char input, Character &actor);

    void chooseTarget(Character &actor);

    void chooseSkill(Character &actor);

    void printTargetChoices(const Skill &skill, const std::vector<Character *> &targets);

    void executeSkillChoice(Character &caster, Character &target, Skill &skill);

    void selectTargetsAndExecuteSkill(Character &actor, Skill &skill);

    void executeSkillChoice(Character &caster, std::vector<Character *> &targets, Skill &skill);
};

#endif