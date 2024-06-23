#include "MapGenerator.h"

std::map<int, Region> MapGenerator::regions;  // 存储所有大区域，使用区域ID作为键

void MapGenerator::generateMapData() {
    int regionId = 1, locationId = 100, npcId = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(3, 5);  // 用于生成小区域和NPC的数量

    for (int i = 0; i < 5; ++i) {
        Region region;
        region.id = regionId++;
        region.name = "Region " + std::to_string(region.id);
        region.description = "Description of " + region.name;

        int numLocations = dis(gen);
        for (int j = 0; j < numLocations; ++j) {
            Location location;
            location.id = locationId++;
            location.name = "Location " + std::to_string(location.id);
            location.description = "Description of " + location.name;

            int numNPCs = dis(gen);
            for (int k = 0; k < numNPCs; ++k) {
                NPC npc;
                npc.id = npcId++;
                npc.name = "NPC " + std::to_string(npc.id);
                npc.description = "Description of " + npc.name;
                location.npcs.push_back(npc);
            }

            region.locations.push_back(location);
        }

        regions[region.id] = region;
    }
}

std::map<int, Region> MapGenerator::getMapData() {
    return regions;
}

void MapGenerator::printMapData() {
    for (auto &[id, region]: regions) {
        std::cout << "Region ID: " << id << ", Name: " << region.name << "\n";
        for (auto &location: region.locations) {
            std::cout << "  Location ID: " << location.id << ", Name: " << location.name << "\n";
            for (auto &npc: location.npcs) {
                std::cout << "    NPC ID: " << npc.id << ", Name: " << npc.name << "\n";
            }
        }
    }
}
