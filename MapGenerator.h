#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>

// NPC 结构
struct NPC {
    int id;
    std::string name;
    std::string description;
};

// 小区域结构
struct Location {
    int id;
    std::string name;
    std::string description;
    std::vector<NPC> npcs;  // 包含NPC列表
};

// 大区域结构
struct Region {
    int id;
    std::string name;
    std::string description;
    std::vector<Location> locations;  // 包含小区域列表
};


class MapGenerator {
public:
    static std::map<int, Region> regions;  // 存储所有大区域，使用区域ID作为键

    static void generateMapData();

    static std::map<int, Region> getMapData();

    static void printMapData();
};
