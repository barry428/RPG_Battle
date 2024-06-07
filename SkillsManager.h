#pragma once

// SkillsManager.h
#ifndef SKILLS_MANAGER_H
#define SKILLS_MANAGER_H

#include "Skill.h"
#include "Character.h"
#include <vector>

class Skill;

class Character;

class SkillsManager {
public:
    // 其它技能
    static std::map<std::string, Skill *> skills;

    // 战士技能
    static std::map<std::string, Skill *> warrior;

    // 法师技能
    static std::map<std::string, Skill *> mage;

    // 牧师技能
    static std::map<std::string, Skill *> priest;

    static void initializeSkills();
};

#endif
