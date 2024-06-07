// Character.cpp
#include <iostream>
#include <fstream>
#include <sstream>

#include "Character.h"
#include "CharacterFactory.h"

void Character::receiveDamage(int damage) {
    attributes["health"] -= damage;
    if (attributes["health"] < 0) {
        attributes["health"] = 0;
    }
}

int Character::attackTarget(Character &target) {
    int damage = getAttribute("attack"); - target.getAttribute("defense");
    damage = damage > 0 ? damage : 0;
    target.receiveDamage(damage);
    return damage;
}

void Character::gainExperience(int exp) {
    experience += exp;
    while (experience >= nextLevelExperience()) {
        levelUp();
    }
}

int Character::nextLevelExperience() {
    // This calculates the sum of all previous experiences required for the next level
    int total = 0;
    for (int i = 1; i < level; i++) {
        total += i * 100;  // Modify this formula as needed
    }
    return total;
}

// 获取属性值，考虑装备加成
int Character::getAttribute(std::string attr) const {
    int baseValue = attributes.at(attr);
    for (const auto &[type, equip]: equipment) {
        baseValue += equip->getAttributeBonus(attr);
    }
    return baseValue;
}

std::string Character::showStatus() {
    return this->name + ": HP "
           + std::to_string(this->getAttribute("health"))
           + "/" + std::to_string(this->getAttribute("maxHealth"))
           + ", MP " + std::to_string(this->getAttribute("mana"))
           + "/" + std::to_string(this->getAttribute("maxMana"));
}

// 保存角色信息到文件
void Character::saveToFile() const {
    std::ofstream outFile("save/" + this->className() + ".txt");
    if (outFile.is_open()) {
        outFile << "type:" << this->className() << std::endl;
        outFile << "name:" << name << std::endl;
        outFile << "desc:" << desc << std::endl;
        outFile << "level:" << level << std::endl;
        outFile << "experience:" << experience << std::endl;
        for (auto it = attributes.begin(); it != attributes.end(); ++it) {
            outFile << "attributes." << it->first << ":" << it->second << std::endl;
        }

        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}


