#include "SkillsManager.h"

std::map<std::string, std::shared_ptr<Skill>> SkillsManager::skills;

// 定义静态成员函数
void SkillsManager::initializeSkills() {
    SkillsManager::skills["火球术+1"] =
            std::make_shared<Skill>("火球术+1", 25,
                                    [](Character &caster, Character &target) {
                                        int damage = 50;  // 例如火球技能的固定伤害
                                        target.receiveDamage(damage);
                                        caster.attributes["mana"] -= 25;
                                    });


    SkillsManager::skills["火焰风暴+1"] =
            std::make_shared<Skill>("火焰风暴+1", 50, SkillType::Area,
                                    [](Character &caster,
                                       std::vector<Character *> &targets) {
                                        for (Character *target: targets) {
                                            if (target->attributes["health"] > 0) {
                                                int damage = 200; // 每个目标固定受到20点伤害
                                                target->receiveDamage(damage);
                                            }
                                        }
                                        caster.attributes["mana"] -= 50;
                                    });

    SkillsManager::skills["嘲讽+1"] =
            std::make_shared<Skill>("嘲讽+1", 15, [](Character &caster, Character &target) {
                caster.attributes["mana"] -= 15;
                // 持续时间 2个回合
            });

    SkillsManager::skills["坚守+1"] =
            std::make_shared<Skill>("坚守+1", 15, [](Character &caster, Character &target) {
                caster.attributes["mana"] -= 15;
                caster.attributes["defense"] += 15;
                // 持续时间 2个回合
            });

    SkillsManager::skills["治疗术+1"] =
            std::make_shared<Skill>("治疗术+1", 20, SkillTarget::Ally,
                                    [](Character &caster, Character &target) {
                                        int healing = 50;
                                        target.attributes["health"] += healing;
                                        if (target.attributes["health"] >
                                            target.attributes["maxHealth"])
                                            target.attributes["health"] = target.attributes["maxHealth"];
                                        caster.attributes["mana"] -= 25;
                                    });

    SkillsManager::skills["治疗波+1"] =
            std::make_shared<Skill>("治疗波+1", 30, SkillType::Area, SkillTarget::Ally,
                                    [](Character &caster,
                                       std::vector<Character *> &targets) {
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
                                    });

}

void SkillsManager::initializeCharacterSkills(Character *c, std::string name) {
    if (name == "warrior") {
        c->skills.push_back(SkillsManager::skills["嘲讽+1"]);
        c->skills.push_back(SkillsManager::skills["坚守+1"]);
    }

    if (name == "mage") {
        c->skills.push_back(SkillsManager::skills["火球术+1"]);
        c->skills.push_back(SkillsManager::skills["火焰风暴+1"]);
    }

    if (name == "priest") {
        c->skills.push_back(SkillsManager::skills["治疗术+1"]);
        c->skills.push_back(SkillsManager::skills["治疗波+1"]);
    }
}

std::shared_ptr<Skill> SkillsManager::getSkill(std::string skillName) {
    return SkillsManager::skills.at(skillName);
}



