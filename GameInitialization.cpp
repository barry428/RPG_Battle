// 在游戏或特定场景初始化中
#include "GameInitialization.h"
#include "SkillsManager.h"
#include "Character.h"
#include "CharacterFactory.h"
#include <random>

std::vector<Character *> GameInitialization::characters;
std::vector<Character *> GameInitialization::enemies;

void GameInitialization::initializeCharacters() {
    SkillsManager::initializeSkills(); // 确保技能已初始化

    // 将角色添加到全局角色列表中
    GameInitialization::characters.push_back(CharacterFactory::loadFromFile("save/Warrior.txt"));
    GameInitialization::characters.push_back(CharacterFactory::loadFromFile("save/Mage.txt"));
    GameInitialization::characters.push_back(CharacterFactory::loadFromFile("save/Priest.txt"));


    // 定义敌方角色原型
    GameInitialization::initEnemies();
}

// 随机生成敌人
void GameInitialization::initEnemies() {
    Character *goblin = new Enemy("哥布林", 50, 0, 15, 3, 8);
    Character *orc = new Enemy("兽人战士", 100, 0, 20, 5, 4);
    Character *troll = new Enemy("巨魔战士", 120, 0, 25, 6, 3);

    // 随机选择1-4个敌方角色为当前场景
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
