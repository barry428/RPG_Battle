
#include "SkillsManager.h"

// 定义静态成员变量
std::vector<Skill *> SkillsManager::skills;

// 定义静态成员函数
void SkillsManager::initializeSkills() {
    // 攻击技能
    skills.push_back(new Skill("Fireball", 25, [](Character &caster, Character &target) {
        int damage = 50;  // 例如火球技能的固定伤害
        target.receiveDamage(damage);
        caster.mana -= 25;
    }));

    // 示例群体伤害技能：火焰风暴
    skills.push_back(new Skill("Firestorm", 50, SkillType::Area, SkillTarget::Enemy,
                               [](Character &caster, std::vector<Character *> &targets) {
                                   for (Character *target: targets) {
                                       if (target->health > 0) {
                                           int damage = 20; // 每个目标固定受到20点伤害
                                           target->receiveDamage(damage);
                                       }
                                   }
                                   caster.mana -= 50;
                               }));

    // 治疗技能
    skills.push_back(new Skill("Heal", 20, SkillTarget::Ally, [](Character &caster, Character &target) {
        int healing = 40;
        target.health += healing;
        if (target.health > target.maxHealth) target.health = target.maxHealth;
        caster.mana -= 20;
    }));

    // 示例增益技能：治愈波
    skills.push_back(new Skill("Healing Wave", 30, SkillType::Area, SkillTarget::Ally,
                               [](Character &caster, std::vector<Character *> &targets) {
                                   for (Character *target: targets) {
                                       if (target->health > 0) {
                                           int healing = 25; // 每个目标恢复25点生命值
                                           target->health += healing;
                                           if (target->health > target->maxHealth) {
                                               target->health = target->maxHealth; // 生命值不能超过最大生命值
                                           }
                                       }
                                   }
                                   caster.mana -= 30;
                               }));

    // 复活技能
    skills.push_back(new Skill("Resurrection", 50, SkillTarget::Ally, true, [](Character &caster, Character &target) {
        if (target.health <= 0) {
            target.health = target.maxHealth / 2;  // 复活至最大生命值的一半
        }
        caster.mana -= 50;
    }));

    // Buff 技能
    skills.push_back(new Skill("Battle Cry", 15, [](Character &caster, Character &target) {
        target.attack += 10;  // 提高目标的攻击力
        caster.mana -= 15;
    }));

}

