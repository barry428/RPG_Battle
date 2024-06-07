// Battle.cpp
#include "Battle.h"
#include "GameInitialization.h"
#include <string>
#include <random>

Battle::Battle(GameWindow *lw, GameWindow *aw, GameWindow *ew, GameWindow *cw)
        : logWin(lw), alliesWin(aw), enemiesWin(ew), commandWin(cw) {
    initializeCharacters();
}

void Battle::initializeCharacters() {
    allies.insert(allies.end(), GameInitialization::characters.begin(), GameInitialization::characters.end());
    enemies.insert(enemies.end(), GameInitialization::enemies.begin(), GameInitialization::enemies.end());
}

/**
* 获取我方角色信息
* @return
*/
std::vector<std::string> Battle::alliesInfo() {
    std::vector<std::string> status;
    for (const auto &character: GameInitialization::characters) {
        status.push_back(character->showStatus());
    }
    return status;
}

/**
 * 获取敌人信息
 * @return
 */
std::vector<std::string> Battle::enemiesInfo() {
    std::vector<std::string> status;
    for (const auto &character: GameInitialization::enemies) {
        status.push_back(character->showStatus());
    }
    return status;
}

/**
 * 检查战斗结果，其中一方全部阵亡则战斗结束
 * @return
 */
int Battle::checkBattleRes() {
    bool aStatus = false, eStatus = false;

    for (auto &enemy: enemies) {
        if (enemy->getAttribute("health") > 0) {
            eStatus = true;
            break;
        }
    }

    if (eStatus == false) {

        // 给与所有角色经验奖励
        int experience = 0;
        for (auto &enemy: enemies) {
            experience += enemy->experience;
        }
        logWin->printLog(logEntries, "玩家胜利，共计获得经验值：" + std::to_string(experience));

        for (auto &allie: allies) {
            allie->gainExperience(experience);
            allie->saveToFile();
        }

        return -2;
    }


    for (auto &allie: allies) {
        if (allie->getAttribute("health") > 0) {
            aStatus = true;
            break;
        }
    }

    if (aStatus == false) {
        logWin->printLog(logEntries, "玩家战败!");
        return -1;
    }
    return 1;
}

/**
 * 循环处理每一轮战斗
 */
void Battle::runBattle() {
    // 检查敌我双方是否有一方已经全部阵亡
    while (checkBattleRes() == 1) {
        alliesWin->updateStatus(alliesInfo());
        enemiesWin->updateStatus(enemiesInfo());
        executeTurn();
    }

    alliesWin->updateStatus(alliesInfo());
    enemiesWin->updateStatus(enemiesInfo());
}

/**
 * 敌方行动，随机攻击一个玩家角色
 * @param actor
 */
void Battle::executeEnemyAction(Character &actor) {
    std::vector<int> aliveTargets;
    for (int i = 0; i < allies.size(); ++i) {
        if (allies[i]->getAttribute("health") > 0) {
            aliveTargets.push_back(i);
        }
    }

    if (!aliveTargets.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, aliveTargets.size() - 1);
        int targetIndex = aliveTargets[dis(gen)];

        logWin->printLog(logEntries, actor.name + " 攻击 " + allies[targetIndex]->name);
        actor.attackTarget(*allies[targetIndex]);
        if (allies[targetIndex]->getAttribute("health") <= 0) {
            logWin->printLog(logEntries, allies[targetIndex]->name + " 被击败!");
        }
    }
    nextTurn();
}

/**
 * 角色开始行动
 */
void Battle::executeTurn() {
    Character *actor = isAlliesTurn ? allies[currentTurn] : enemies[currentTurn];
    if (actor->getAttribute("health") > 0) {
        logWin->printLog(logEntries, actor->name + "开始行动！");
        if (isAlliesTurn) {
            handleAction(*actor);
        } else {
            executeEnemyAction(*actor);
        }
    } else {
        // 跳过已死亡的角色
        nextTurn();
    }
}

/**
 * 如果其中一方全部行动完成，进入下一回合，由对方开始行动
 */
void Battle::nextTurn() {
    currentTurn++;
    if (isAlliesTurn) {
        if (currentTurn >= allies.size()) {
            isAlliesTurn = !isAlliesTurn;
            currentTurn = 0;
        }
    } else {
        if (currentTurn >= enemies.size()) {
            isAlliesTurn = !isAlliesTurn;
            currentTurn = 0;
        }
    }
}

void Battle::handleAction(Character &actor) {
    // 我方角色行动，展示操作菜单
    displayMainMenu();
    char input = wgetch(commandWin->win);

    // 更准确地检查无效输入
    if (input != EOF && input != '\0') {
        executeMainMenu(input, actor);
    }
}


void Battle::displayMainMenu() {
    commandWin->displayCommand("选择行动方式: 攻击 (a), 防御 (d), 技能 (s)");
}

void Battle::printAttackTargets() {
    std::string msg = "选择你要攻击的对象: ";
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getAttribute("health") > 0) {
            msg += std::to_string(i + 1) + "." + enemies[i]->name + " ";
        }
    }
    commandWin->displayCommand(msg);
}

void Battle::executeMainMenu(char input, Character &actor) {
    switch (input) {
        case 'a': // Attack
            printAttackTargets();
            chooseTarget(actor);
            break;
        case 'd': // Defend
            logWin->printLog(logEntries, "进行防御!");
            displayMainMenu();
            nextTurn();
            break;
        case 's': // Skills
            chooseSkill(actor);
            break;
        default:
            displayMainMenu();
            break;
    }
}

/**
 * 选择攻击目标进行攻击
 * @param actor
 */
void Battle::chooseTarget(Character &actor) {
    char input = wgetch(commandWin->win);
    int index = input - '0' - 1;
    if (input == '0') {
        displayMainMenu();  // Return to main menu
        return;
    }

    try {
        int damage = actor.attackTarget(*enemies.at(index));
        logWin->printLog(logEntries, actor.name + " 对 " + enemies.at(index)->name +"造成伤害：" + std::to_string(damage));
        if (enemies.at(index)->getAttribute("health") <= 0) {
            logWin->printLog(logEntries, enemies.at(index)->name + " 被击败!");
        }
        nextTurn();
    } catch (const std::out_of_range &e) {
        logWin->printLog(logEntries, "无效的输入！");
        logWin->printLog(logEntries, e.what());
    }
}


/**
 * 选择技能使用
 * @param actor
 */
void Battle::chooseSkill(Character &actor) {
    std::string msg = "选择使用的技能: ";
    int i = 1;
    for (auto &skill: actor.skills) {
        msg += std::to_string(i++) + "." + skill->name + " ";
    }
    msg += "0.返回";
    commandWin->displayCommand(msg);

    char input = wgetch(commandWin->win);
    int skillIndex = input - '0' - 1;
    if (skillIndex == -1) {
        displayMainMenu();  // If user selects '0' to return
        return;
    }

    if (skillIndex >= 0 && skillIndex < actor.skills.size()) {
        selectTargetsAndExecuteSkill(actor, *actor.skills.at(skillIndex));
    } else {
        logWin->printLog(logEntries, "无效的输入！");
        commandWin->displayCommand(msg);
    }
}

/**
 * 选择目标发动技能钱的检查
 * @param actor
 * @param skill
 */
void Battle::selectTargetsAndExecuteSkill(Character &actor, Skill &skill) {
    std::vector<Character *> targets = skill.isAllyTarget() ? allies : enemies;

    // 群体攻击
    if (skill.isAreaEffect()) {
        executeSkillChoice(actor, targets, skill);
        return;
    }

    // 单体攻击，炫耀先选择攻击对象
    printTargetChoices(skill, targets);
    int targetIndex = wgetch(commandWin->win) - '0' - 1;

    try {
        std::vector<Character *> tmp;
        tmp.push_back(targets.at(targetIndex));
        executeSkillChoice(actor, tmp, skill);
    } catch (const std::out_of_range &e) {
        logWin->printLog(logEntries, "无效的输入！");
        displayMainMenu();
    }
}

/**
 * 发动技能
 * @param caster
 * @param targets
 * @param skill
 */
void Battle::executeSkillChoice(Character &caster, std::vector<Character *> &targets, Skill &skill) {
    if (caster.getAttribute("mana") < skill.manaCost) {
        logWin->printLog(logEntries, caster.name + "没有足够的魔法施展" + skill.name);
        return;
    }

    if (skill.isAreaEffect()) {
        skill.areaEffect(caster, targets);
        logWin->printLog(logEntries,
                         caster.name + "对" + (skill.isAllyTarget() ? "我" : "敌") + "方全体施展了" + skill.name);
        nextTurn();
        return;
    }

    for (Character *target: targets) {
        skill.effect(caster, *target);
        std::string message = caster.name + "对" + target->name + "施展了" + skill.name;
        logWin->printLog(logEntries, message);
        if (target->getAttribute("health") <= 0) {
            logWin->printLog(logEntries, target->name + "被击败!");
        }
    }
    nextTurn();
}

/**
 * 选择施展技能的目标
 * @param skill
 * @param targets
 */
void Battle::printTargetChoices(const Skill &skill, const std::vector<Character *> &targets) {
    std::string msg = "选择技能释放的对象: ";
    int i = 1;
    for (auto &targets: targets) {
        if (skill.isForDead() && targets->getAttribute("health") == 0 ||
            !skill.isForDead() && targets->getAttribute("health") > 0) {
            msg += std::to_string(i++) + "." + targets->name + " ";
        }
    }
    msg += "0.返回";
    commandWin->displayCommand(msg);
}


