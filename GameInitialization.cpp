// 在游戏或特定场景初始化中
#include "GameInitialization.h"
#include "SkillsManager.h"
#include <random>

std::vector<Character *> GameInitialization::characters;
std::vector<Character *> GameInitialization::enemies;

void GameInitialization::initializeCharacters() {
    SkillsManager::initializeSkills(); // 确保技能已初始化

    // 创建并初始化法师
    Character *mage = new Character("法师", 70, 150, 20, 4, 6);
    mage->skills.push_back(SkillsManager::skills[0]); // Fireball
    mage->skills.push_back(SkillsManager::skills[1]); // Firestorm
    mage->desc = "法师是一个擅长远程攻击和施放强大法术的角色，能够造成大量的魔法伤害，但身体较为脆弱。";

    // 创建并初始化战士
    Character *warrior = new Character("战士", 120, 50, 30, 10, 5);
    warrior->skills.push_back(SkillsManager::skills[5]); // Battle Cry
    warrior->desc = "战士是前线的坚固防御者，具有高生命值和防御力，擅长近战攻击。";

    // 创建并初始化牧师
    Character *priest = new Character("牧师", 80, 130, 20, 5, 7);
    priest->skills.push_back(SkillsManager::skills[2]); // Heal
    priest->skills.push_back(SkillsManager::skills[3]); // 治愈波
    priest->skills.push_back(SkillsManager::skills[4]); // 复活
    priest->desc = "牧师是一个支援角色，擅长治疗和恢复，同时具有弱化敌人的能力。";

    // 将角色添加到全局角色列表中
    GameInitialization::characters.push_back(mage);
    GameInitialization::characters.push_back(warrior);
    GameInitialization::characters.push_back(priest);

    // 处理技能列表可能为空的情况

    // 定义敌方角色原型
    GameInitialization::genEnemies();
}

// 随机生成敌人
void GameInitialization::genEnemies() {
    Character *goblin = new Character("哥布林", 50, 0, 15, 3, 8);
    Character *orc = new Character("兽人战士", 100, 0, 20, 5, 4);
    Character *troll = new Character("巨魔战士", 120, 0, 25, 6, 3);

    // 随机选择3-5个敌方角色为当前场景
    std::vector<Character *> enemyTypes = {goblin, orc, troll};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 4); // 随机数在1到4之间
    int numEnemies = dist(gen);

    // 清空之前的敌人列表
    GameInitialization::enemies.clear();
    std::uniform_int_distribution<> pickEnemy(0, enemyTypes.size() - 1);

    for (int i = 0; i < numEnemies; ++i) {
        int idx = pickEnemy(gen);
        // 使用复制构造函数或者创建一个类似克隆的函数来复制原型
        Character *newEnemy = new Character(*enemyTypes[idx]);
        GameInitialization::enemies.push_back(newEnemy);
    }
}

// 清理全局角色列表和敌人列表的内存，应在游戏结束时调用
void GameInitialization::cleanup() {
    for (auto enemy: GameInitialization::enemies) delete enemy;
    GameInitialization::characters.clear();
    GameInitialization::enemies.clear();
}
