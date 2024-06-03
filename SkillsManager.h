// SkillsManager.h
#ifndef SKILLS_MANAGER_H
#define SKILLS_MANAGER_H

#include "Skill.h"
#include <vector>

class SkillsManager {
public:
    static std::vector<Skill*> skills;
    static void initializeSkills();
};

#endif
