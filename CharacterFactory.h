#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <sstream>

#include "Character.h"

class CharacterFactory {
public:
    static Character *
    createCharacter(const std::string &type, const std::string &name, const std::string &desc, int experience,
                    int level) {
        if (type == "Warrior") {
            return new Warrior(name, desc, experience, level);
        }
        if (type == "Mage") {
            return new Mage(name, desc, experience, level);
        }
        if (type == "Priest") {
            return new Priest(name, desc, experience, level);
        }
        // 添加其他类型
        throw std::runtime_error("Unsupported character type: " + type);
    }

    static Character *loadFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        std::string type, name, desc, line;
        int level = 0, experience = 0;
        Character *character = nullptr;
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (getline(iss, key, ':') && getline(iss, value)) {
                if (key == "type") type = value;
                else if (key == "name") name = value;
                else if (key == "desc") desc = value;
                else if (key == "level") level = stoi(value);
                else if (key == "experience") experience = stoi(value);
                else if (key.find("attributes.") == 0) {
                    std::string attrName = key.substr(11);
                    if (character == nullptr) {
                        character = CharacterFactory::createCharacter(type, name, desc, experience, level);
                    }
                    character->setAttribute(attrName, value);
                }
            }
        }

        if (character != nullptr) {
            character->unlockSkills();
        } else {
            throw std::runtime_error("Failed to create character of type: " + type);
        }

        file.close();
        return character;
    }
};
