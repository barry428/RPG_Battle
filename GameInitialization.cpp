// 在游戏或特定场景初始化中
#include "GameInitialization.h"
#include "SkillsManager.h"
#include "Character.h"
#include "CharacterFactory.h"
#include <random>

std::vector<Character *> GameInitialization::characters;
std::vector<Character *> GameInitialization::enemies;

void GameInitialization::initializeCharacters() {
    SkillsManager::initializeSkills();

    // 将角色添加到全局角色列表中
    Character *warrior = CharacterFactory::loadFromFile("save/Warrior.txt");
    SkillsManager::initializeCharacterSkills(warrior, "warrior");
    GameInitialization::characters.push_back(warrior);

    Character *mage = CharacterFactory::loadFromFile("save/Mage.txt");
    SkillsManager::initializeCharacterSkills(mage, "mage");
    GameInitialization::characters.push_back(mage);

    Character *priest = CharacterFactory::loadFromFile("save/Priest.txt");
    SkillsManager::initializeCharacterSkills(priest, "priest");
    GameInitialization::characters.push_back(priest);

    // 定义敌方角色原型
    GameInitialization::initEnemies();
}

// 随机生成敌人
void GameInitialization::initEnemies() {
    std::vector<Character *> enemyTypes;

    enemyTypes.push_back(new Enemy("哥布林", 50, 0, 15, 3, 8));
    enemyTypes.push_back(new Enemy("兽人战士", 100, 0, 20, 5, 4));
    enemyTypes.push_back(new Enemy("巨魔战士", 120, 0, 25, 6, 3));
    enemyTypes.push_back(new Enemy("暗影刺客", 70, 0, 30, 2, 10));
    enemyTypes.push_back(new Enemy("骷髅战士", 60, 0, 18, 4, 6));
    enemyTypes.push_back(new Enemy("沼泽巨怪", 150, 0, 20, 8, 2));
    enemyTypes.push_back(new Enemy("山地巨人", 200, 0, 35, 7, 3));
    enemyTypes.push_back(new Enemy("亡灵巫师", 80, 25, 22, 3, 7));
    enemyTypes.push_back(new Enemy("荒野狼人", 90, 0, 23, 5, 7));
    enemyTypes.push_back(new Enemy("火焰元素", 100, 50, 30, 4, 5));
    enemyTypes.push_back(new Enemy("冰霜巨人", 130, 0, 25, 10, 3));
    enemyTypes.push_back(new Enemy("食人魔", 140, 0, 28, 6, 4));
    enemyTypes.push_back(new Enemy("沙漠蜘蛛", 80, 0, 20, 3, 9));
    enemyTypes.push_back(new Enemy("毒蛇", 40, 0, 12, 2, 12));
    enemyTypes.push_back(new Enemy("幽灵", 70, 30, 25, 1, 10));
    enemyTypes.push_back(new Enemy("吸血鬼", 120, 20, 35, 4, 9));
    enemyTypes.push_back(new Enemy("岩石傀儡", 160, 0, 30, 12, 2));
    enemyTypes.push_back(new Enemy("水元素", 100, 40, 28, 5, 6));
    enemyTypes.push_back(new Enemy("风暴召唤者", 90, 50, 32, 3, 8));
    enemyTypes.push_back(new Enemy("沼泽巫师", 110, 45, 27, 5, 5));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(2, 4); // 随机数在2到4之间
    int numEnemies = dist(gen);

    // 清空之前的敌人列表
    GameInitialization::enemies.clear();
    std::uniform_int_distribution<> pickEnemy(0, enemyTypes.size() - 1);

    for (int i = 0; i < numEnemies; ++i) {
        int idx = pickEnemy(gen);
        // 使用复制构造函数或者创建一个类似克隆的函数来复制原型
        Character *newEnemy = enemyTypes[idx]->clone();
        GameInitialization::enemies.push_back(newEnemy);
    }
}

// 清理全局角色列表和敌人列表的内存，应在游戏结束时调用
void GameInitialization::cleanup() {
    for (auto enemy: GameInitialization::enemies) delete enemy;
    GameInitialization::characters.clear();
    GameInitialization::enemies.clear();
}
