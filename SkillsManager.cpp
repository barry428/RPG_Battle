#pragma once

#include "SkillsManager.h"

std::map<std::string, Skill *> SkillsManager::skills;
std::map<std::string, Skill *> SkillsManager::warrior;
std::map<std::string, Skill *> SkillsManager::mage;
std::map<std::string, Skill *> SkillsManager::priest;

// 定义静态成员函数
void SkillsManager::initializeSkills() {

}

