#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cxxabi.h>
#include "SkillsManager.h"
#include "Equipment.h"

class Skill;

class SkillsManager;

class Equipment;

class Character {
public:
    std::string name;
    std::string desc;
    int level = 1;
    int experience = 0;
    std::map<std::string, int> attributes;
    std::map<EquipmentType, Equipment *> equipment;
    std::vector<std::shared_ptr<Skill>> skills;

    virtual ~Character() {}

    virtual void initializeAttributes() = 0;  // 初始化特定属性

    virtual void setAttribute(const std::string &key, const std::string &value) = 0;  // 处理特定属性

    virtual Character *clone() const = 0; // 纯虚函数，强制派生类实现它

    virtual void levelUp() {
        level++;
        increaseStats();
        unlockSkills();
    }

    std::string className() const {
        int status;
        std::unique_ptr<char, void (*)(void *)> res{
                abi::__cxa_demangle(typeid(*this).name(), NULL, NULL, &status),
                std::free
        };
        return (status == 0) ? res.get() : typeid(*this).name();
    }

    virtual void increaseStats() = 0;

    virtual void unlockSkills() = 0;

    virtual int experienceToNextLevel() const = 0;

    void receiveDamage(int damage);

    int attackTarget(Character &target);

    void gainExperience(int exp);

    int nextLevelExperience();

    // 获取属性值，考虑装备加成
    int getAttribute(std::string attr) const;

    std::string showStatus();

    // 保存角色信息到文件
    void saveToFile() const;
};


class Allies : public Character {

public:

    Allies(const std::string &name, const std::string &desc, int experience, int level) {
        this->name = name;
        this->desc = desc;
        this->experience = experience;
        this->level = level;
    }

    void unlockSkills() override{};
    void initializeAttributes() override{};

    int experienceToNextLevel() const override {
        return 100 * level * level;
    }

    void setAttribute(const std::string &key, const std::string &value) override {
        attributes[key] = std::stoi(value);
    }
};


class Warrior : public Allies {
public:
    using Allies::Allies;

    void increaseStats() override {
        std::string name = "战士+" + std::to_string(level / 10 + 1);
        attributes["maxHealth"] += (level / 10) * 20 + 40;
        attributes["maxMana"] += (level / 10) * 10 + 40;
        attributes["health"] = attributes["maxHealth"];
        attributes["mana"] = attributes["maxMana"];
    }

    void unlockSkills() override {

    }

    Character *clone() const override {
        return new Warrior(*this);
    }
};


class Mage : public Allies {
public:
    using Allies::Allies;

    void increaseStats() override {
        std::string name = "法师+" + std::to_string(level / 10 + 1);
        attributes["maxHealth"] += (level / 10) * 10 + 40;
        attributes["maxMana"] += (level / 10) * 20 + 40;
        attributes["health"] = attributes["maxHealth"];
        attributes["mana"] = attributes["maxMana"];
    }

    void unlockSkills() override {

    }

    Character *clone() const override {
        return new Mage(*this);
    }
};


class Priest : public Allies {
public:
    using Allies::Allies;

    void increaseStats() override {
        std::string name = "牧师+" + std::to_string(level / 10 + 1);
        attributes["maxHealth"] += (level / 10) * 10 + 40;
        attributes["maxMana"] += (level / 10) * 20 + 40;
        attributes["health"] = attributes["maxHealth"];
        attributes["mana"] = attributes["maxMana"];
    }

    void unlockSkills() override {

    }

    Character *clone() const override {
        return new Priest(*this);
    }
};


class Enemy : public Character {
public:
    Enemy(std::string name, int health, int mana, int attack, int defense, int speed)
            : Character() {
        this->name = name;
        this->experience = 100;
        attributes["health"] = health;
        attributes["maxHealth"] = health;
        attributes["mana"] = mana;
        attributes["maxMana"] = mana;
        attributes["attack"] = attack;
        attributes["defense"] = defense;
        attributes["speed"] = speed;
    }

    void increaseStats() override {
    }

    void unlockSkills() override {

    }

    int experienceToNextLevel() const override {
        return 100 * level * level;
    }

    void initializeAttributes() override {

    }

    void setAttribute(const std::string &key, const std::string &value) override {
        attributes[key] = std::stoi(value);
    }

    Character *clone() const override {
        return new Enemy(*this);
    }
};

