#pragma once

#include <string>
#include <map>

enum class EquipmentType { Helmet, Armor, Weapon, Shield };

class Equipment {
public:
    std::string name;
    EquipmentType type;
    std::map<std::string, int> attributeBonuses;

    Equipment(std::string n, EquipmentType t, std::map<std::string, int> bonuses)
            : name(n), type(t), attributeBonuses(bonuses) {}

    int getAttributeBonus(std::string attr) const {
        if (attributeBonuses.find(attr) != attributeBonuses.end()) {
            return attributeBonuses.at(attr);
        }
        return 0;
    }
};
