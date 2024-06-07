// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cxxabi.h>
#include "Skill.h"
#include "SkillType.h"
#include "SkillTarget.h"
#include "Equipment.h"

class Skill;

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
        switch (level / 10) {
            case 0:
                attributes["maxHealth"] += 40;
                attributes["maxMana"] += 20;
                name = "战士+1";
                break;
            case 1:
                attributes["maxHealth"] += 60;
                attributes["maxMana"] += 30;
                name = "战士+2";
                break;
            case 2:
                attributes["maxHealth"] += 80;
                attributes["maxMana"] += 40;
                name = "战士+3";
                break;
            case 3:
                attributes["maxHealth"] += 100;
                attributes["maxMana"] += 50;
                name = "战士+4";
                break;
        }
        attributes["health"] = attributes["maxHealth"];
        attributes["mana"] = attributes["maxMana"];
    }

    void unlockSkills() override {
        skills.push_back(std::make_shared<Skill>("嘲讽+1", 15, [](Character &caster, Character &target) {
            caster.attributes["mana"] -= 15;
            // 持续时间 2个回合
        }));

        skills.push_back(std::make_shared<Skill>("坚守+1", 15, [](Character &caster, Character &target) {
            caster.attributes["mana"] -= 15;
            caster.attributes["defense"] += 15;
            // 持续时间 2个回合
        }));

    }

    Character *clone() const override {
        return new Warrior(*this);
    }
};


class Mage : public Allies {
public:
    using Allies::Allies;

    void increaseStats() override {
        switch (level / 10) {
            case 0:
                attributes["maxHealth"] += 20;
                attributes["maxMana"] += 40;
                name = "法师+1";
                break;
            case 1:
                attributes["maxHealth"] += 30;
                attributes["maxMana"] += 60;
                name = "法师+2";
                break;
            case 2:
                attributes["maxHealth"] += 40;
                attributes["maxMana"] += 80;
                name = "法师+3";
                break;
            case 3:
                attributes["maxHealth"] += 50;
                attributes["maxMana"] += 100;
                name = "法师+4";
                break;
        }
        attributes["health"] = attributes["maxHealth"];
        attributes["mana"] = attributes["maxMana"];
    }

    void unlockSkills() override {
        skills.push_back(std::make_shared<Skill>("火球术+1", 25, [](Character &caster, Character &target) {
            int damage = 50;  // 例如火球技能的固定伤害
            target.receiveDamage(damage);
            caster.attributes["mana"] -= 25;
        }));

        skills.push_back(std::make_shared<Skill>("火焰风暴+1", 50, SkillType::Area,
                                                 [](Character &caster, std::vector<Character *> &targets) {
                                                     for (Character *target: targets) {
                                                         if (target->attributes["health"] > 0) {
                                                             int damage = 200; // 每个目标固定受到20点伤害
                                                             target->receiveDamage(damage);
                                                         }
                                                     }
                                                     caster.attributes["mana"] -= 50;
                                                 }));
    }

    Character *clone() const override {
        return new Mage(*this);
    }
};


class Priest : public Allies {
public:
    using Allies::Allies;

    void increaseStats() override {
        switch (level / 10) {
            case 0:
                attributes["maxHealth"] += 20;
                attributes["maxMana"] += 40;
                name = "牧师+1";
                break;
            case 1:
                attributes["maxHealth"] += 30;
                attributes["maxMana"] += 60;
                name = "牧师+2";
                break;
            case 2:
                attributes["maxHealth"] += 40;
                attributes["maxMana"] += 80;
                name = "牧师+3";
                break;
            case 3:
                attributes["maxHealth"] += 50;
                attributes["maxMana"] += 100;
                name = "牧师+4";
                break;
        }
        attributes["health"] = attributes["maxHealth"];
        attributes["mana"] = attributes["maxMana"];
    }

    void unlockSkills() override {
        skills.push_back(std::make_shared<Skill>("治疗术+1", 20, SkillTarget::Ally,
                                                 [](Character &caster, Character &target) {
                                                     int healing = 50;
                                                     target.attributes["health"] += healing;
                                                     if (target.attributes["health"] >
                                                         target.attributes["maxHealth"])
                                                         target.attributes["health"] = target.attributes["maxHealth"];
                                                     caster.attributes["mana"] -= 25;
                                                 }));

        skills.push_back(std::make_shared<Skill>("治疗波+1", 30, SkillType::Area, SkillTarget::Ally,
                                                 [](Character &caster, std::vector<Character *> &targets) {
                                                     for (Character *target: targets) {
                                                         if (target->attributes["health"] > 0) {
                                                             int healing = 20; // 每个目标恢复25点生命值
                                                             target->attributes["health"] += healing;
                                                             if (target->attributes["health"] >
                                                                 target->attributes["maxHealth"]) {
                                                                 target->attributes["health"] = target->attributes["maxHealth"]; // 生命值不能超过最大生命值
                                                             }
                                                         }
                                                     }
                                                     caster.attributes["mana"] -= 30;
                                                 }));
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

#endif
