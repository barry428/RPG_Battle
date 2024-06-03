// 在游戏或特定场景初始化中
#include "SkillsManager.h"
#include "Character.h"
#include <vector>

class GameInitialization {
public:
    static std::vector<Character *> characters;  // 在其他文件中定义
    static std::vector<Character *> enemies;  // 在其他文件中定义

    static void initializeCharacters();
    static void genEnemies();
    static void cleanup();
};