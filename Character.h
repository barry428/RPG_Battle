// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Skill.h"  // 首先包含 Skill
#include "Character.h"  // 然后包含 Character

class Skill; // 前向声明

class Character {
public:
    std::string name;
    std::string desc;
    int health, maxHealth, mana, maxMana, attack, defense, speed;
    std::vector<Skill *> skills;  // 使用指针存储技能

    Character(std::string n, int hp, int maxHp, int mp, int maxMp, int atk, int def, int spd);
    Character(std::string n, int hp, int mp, int atk, int def, int spd);

    void receiveDamage(int damage);

    void attackTarget(Character &target);

    Character *clone() const;  // 添加克隆方法
};

#endif