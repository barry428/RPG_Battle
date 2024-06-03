// Character.cpp
#include "Character.h"

Character::Character(std::string n, int hp, int maxHp, int mp, int maxMp, int atk, int def, int spd)
        : name(n), health(hp), maxHealth(maxHp), mana(mp), maxMana(maxMp), attack(atk), defense(def), speed(spd) {}

Character::Character(std::string n, int hp, int mp, int atk, int def, int spd)
        : name(n), health(hp), maxHealth(hp), mana(mp), maxMana(mp), attack(atk), defense(def), speed(spd) {}

void Character::receiveDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

void Character::attackTarget(Character &target) {
    int damage = attack - target.defense;
    damage = damage > 0 ? damage : 0;
    if (target.health >= damage) {
        target.receiveDamage(damage);
    } else {
        target.receiveDamage(target.health);
    }
}

Character *Character::clone() const {
    return new Character(name, health, mana, attack, defense, speed);
}