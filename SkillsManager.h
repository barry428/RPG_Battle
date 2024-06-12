#pragma once

#include "Skill.h"
#include <vector>
#include <map>

class Skill;

class Character;

class SkillsManager {
public:
    static std::map<std::string, std::shared_ptr<Skill>> skills;

    static void initializeSkills();

    static std::shared_ptr<Skill> getSkill(std::string skillName);

    static void initializeCharacterSkills(Character *c, std::string name);
};

