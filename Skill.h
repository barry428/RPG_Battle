// Skill.h
#pragma once

#include <string>
#include <functional>
#include "Character.h"
#include "SkillType.h"
#include "SkillTarget.h"

class Character;

class Skill {
public:
    std::string name;
    int manaCost;
    SkillType type = SkillType::Single;
    SkillTarget target = SkillTarget::Enemy;
    bool forDead = false;
    std::function<void(Character &caster, Character &target)> effect;
    std::function<void(Character &caster, std::vector<Character *> &targets)> areaEffect;

    //单体技能
    Skill(std::string n, int cost, std::function<void(Character &caster, Character &target)> eff)
            : name(n), manaCost(cost), effect(eff) {}

    //可以对我方释放的技能
    Skill(std::string n, int cost, SkillTarget trgt,
          std::function<void(Character &caster, Character &target)> eff)
            : name(n), manaCost(cost), target(trgt), effect(eff) {}

    //可以对我方已经死亡的角色释放的技能
    Skill(std::string n, int cost, SkillTarget trgt, bool forDead,
          std::function<void(Character &caster, Character &target)> eff)
            : name(n), manaCost(cost), target(trgt), forDead(forDead), effect(eff) {}

    //群体技能
    Skill(std::string n, int cost, SkillType tp,
          std::function<void(Character &caster, std::vector<Character *> &targets)> eff)
            : name(n), manaCost(cost), type(tp), areaEffect(eff) {}

    //可以对我方释放的群体技能
    Skill(std::string n, int cost, SkillType tp, SkillTarget trgt,
          std::function<void(Character &caster, std::vector<Character *> &targets)> eff)
            : name(n), manaCost(cost), type(tp), target(trgt), areaEffect(eff) {}

    bool isAreaEffect() const {
        return type == SkillType::Area;
    }

    bool isAllyTarget() const {
        return target == SkillTarget::Ally;
    }

    bool isForDead() const {
        return forDead;
    }

};

